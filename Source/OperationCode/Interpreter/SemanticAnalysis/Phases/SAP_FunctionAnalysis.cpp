// Fill out your copyright notice in the Description page of Project Settings.

#include "SAP_FunctionAnalysis.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/SemanticAnalysis/SymbolTable.h"

#include "Interpreter/Parser/AST/AST_Basic.h"
#include "Interpreter/Parser/AST/AST_Main.h"

#include "Interpreter/Parser/AST/Definition/AST_ClassDefinition.h"
#include "Interpreter/Parser/AST/Definition/AST_FunctionDefinition.h"




/*======================
 Basic
======================*/

void USAP_FunctionAnalysis::Analyse(UAST_Basic* Basic)
{
	AnalyseChildren(Basic);
}


/*======================
 Main
======================*/

void USAP_FunctionAnalysis::Analyse(UAST_Main* Main)
{
	AnalyseChildren(Main);
}


/*======================
 Class definition
======================*/

void USAP_FunctionAnalysis::Analyse(UAST_ClassDefinition* ClassDefinition)
{
	// Store this class as parent
	owningClass = ClassDefinition;

	// Loop through all function definitions
	for (UAST_FunctionDefinition* functionDefinition : ClassDefinition->FunctionDefinitions)
	{
		functionDefinition->Analyse(this);
	}

	// Remove class as parent
	owningClass = nullptr;
}


/*======================
 Function definition
======================*/

void USAP_FunctionAnalysis::Analyse(UAST_FunctionDefinition* FunctionDefinition)
{
	// Check if it is a constructor
	if (FunctionDefinition->FunctionData.FunctionName == "constructor")
	{
		if (!owningClass)
		{
			ThrowError("Constructors must be defined inside a class.");
			return;
		}

		// Store constructor
		FunctionDefinition->FunctionData.FunctionName = owningClass->Name;
		FunctionDefinition->FunctionData.ReturnType = owningClass->Name;
		GetSymbolTable()->Constructors.FindOrAdd(owningClass).constructors.Add(FunctionDefinition);
	}

	CheckTypeValidity(FunctionDefinition, owningClass);
	if (HasErrors()) return;

	CheckDuplicateFunctions(FunctionDefinition, owningClass);
	if (HasErrors()) return;

	CheckDuplicateArgumentName(FunctionDefinition, owningClass);
	if (HasErrors()) return;

	// If there is no owning class, this function exists inside global scope, therefore it cannot be overriden
	if (owningClass) CheckOverrideValidity(FunctionDefinition, owningClass);


	// Add Function id to symbol table
	FFunctionSignature sig = FunctionDefinition->FunctionData.GetSignature();
	GetSymbolTable()->FunctionIDs.Add(FFunctionID(sig, owningClass), FunctionDefinition);

}



void USAP_FunctionAnalysis::CheckTypeValidity(UAST_FunctionDefinition* FunctionDefinition, UAST_ClassDefinition* ownerClass)
{
	// Check parameter types
	for (FParameterData paramData : FunctionDefinition->FunctionData.ParameterData)
	{
		// We cant know the array type now, so we skip.
		if (paramData.Type == "element type") continue;

		if (!GetSymbolTable()->ClassNames.Contains(paramData.Type))
		{
			ThrowError("Undefined type \"" + paramData.Type + "\" detected in function \"" + FunctionDefinition->FunctionData.FunctionName + "\".");
		}
	}

	// Check return value
	FString returnType = FunctionDefinition->FunctionData.ReturnType;

	// Cannot know the type yet. Skip.
	if (returnType == "element type") return;

	if (!GetSymbolTable()->ClassNames.Contains(returnType) && returnType != "void")
	{
		ThrowError("Undefined return type \"" + returnType + "\" detected in function \"" + FunctionDefinition->FunctionData.FunctionName + "\".");
	}
}

void USAP_FunctionAnalysis::CheckDuplicateFunctions(UAST_FunctionDefinition* FunctionDefinition, UAST_ClassDefinition* ownerClass)
{
	// Store signature
	FFunctionSignature sig = FunctionDefinition->FunctionData.GetSignature();

	// if parent class is nullptr, then this class is defined in global scope
	FFunctionID ID = FFunctionID(sig, ownerClass);

	// Throw error if this function is a duplicate
	if (GetSymbolTable()->FunctionIDs.Contains(ID))
	{
		FString location = ownerClass ? "class \"" + ownerClass->Name + "\"" : "global scope";
		ThrowError("Duplicate function \"" + sig.FunctionName + "\" detected in " + location + ".");
		return;
	}
}

void USAP_FunctionAnalysis::CheckDuplicateArgumentName(UAST_FunctionDefinition* FunctionDefinition, UAST_ClassDefinition* ownerClass)
{
	TSet<FString> ArgumentNames;
	for (FParameterData paramData : FunctionDefinition->FunctionData.ParameterData)
	{
		if (ArgumentNames.Contains(paramData.Name))
		{
			FString location = ownerClass ? "class \"" + ownerClass->Name + "\"" : "global scope";
			ThrowError("Function \"" + FunctionDefinition->FunctionData.FunctionName + "\" in " + location
				+ " has multiple arguments with same name: " + paramData.Name);
		}
		else ArgumentNames.Add(paramData.Name);
	}
}

void USAP_FunctionAnalysis::CheckOverrideValidity(UAST_FunctionDefinition* FunctionDefinition, UAST_ClassDefinition* ownerClass)
{
	UAST_ClassDefinition* currentClass = GetSymbolTable()->ClassInheritance[ownerClass];
	// Loop upwards through inheritance chain until we reach the end or overriden function.
	while (currentClass)
	{
		// Loop through parents function definition
		for (UAST_FunctionDefinition* parentFunction : currentClass->FunctionDefinitions)
		{
			// In order for a function to override another, they must have a matching signature
			if (parentFunction->FunctionData.GetSignature() == FunctionDefinition->FunctionData.GetSignature())
			{
				// Override is valid only if return types are same, or child has a derivitive return type
				// Needs manual check in case both functions are void
				if (FunctionDefinition->FunctionData.ReturnType == parentFunction->FunctionData.ReturnType) return;

				UAST_ClassDefinition** childReturnType = GetSymbolTable()->ClassNames.Find(FunctionDefinition->FunctionData.ReturnType);
				UAST_ClassDefinition** parentReturnType = GetSymbolTable()->ClassNames.Find(parentFunction->FunctionData.ReturnType);

				// If both functions are void, the comparison above would return.
				// If neither of them are void, the check underneath will handle it
				// So if either of them is void, this function cannot be a valid override.
				if (!childReturnType || !parentReturnType)
				{
					ThrowError("Function \"" + FunctionDefinition->FunctionData.FunctionName + "\" in class \"" + ownerClass->Name
						+ "\" overrides a function in parent \"" + currentClass->Name + "\" but has a wrong return type.");
					return;
				}

				if (!GetSymbolTable()->IsChildOf(*childReturnType, *parentReturnType))
				{
					ThrowError("Function \"" + FunctionDefinition->FunctionData.FunctionName + "\" in class \"" + ownerClass->Name
						+ "\" overrides a function in parent \"" + currentClass->Name + "\" but has a wrong return type.");
					return;
				}

				// Since we found another function with same signature, we can stop the loop.
				return;
			}
		}

		// Go to next class in chain
		currentClass = GetSymbolTable()->ClassInheritance[currentClass];
	}
}



