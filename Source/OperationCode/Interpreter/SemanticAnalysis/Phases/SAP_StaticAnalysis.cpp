// Fill out your copyright notice in the Description page of Project Settings.

#include "SAP_StaticAnalysis.h"
#include "Interpreter/SemanticAnalysis/SymbolTable.h"


void USAP_StaticAnalysis::StartAnalysis(UAST_Node* Root) 
{
	// Since we already passed through Store statics phase,
	// we dont need to loop through the AST tree to find static functions.
	for (auto it = GetSymbolTable()->StaticFunctions.CreateConstIterator(); it; ++it)
	{
		for (UAST_FunctionDefinition* currentFunctionDefinition : it.Value().Functions)
		{
			// Skip if constructor
			if (GetSymbolTable()->ClassNames.Contains(currentFunctionDefinition->FunctionData.FunctionName)) continue;

			// Add arguments as local variables
			LocalVariableNames.Empty();
			for (FParameterData params : currentFunctionDefinition->FunctionData.ParameterData)
			{
				LocalVariableNames.Add(params.Name);
			}

			// Get owning class if it exists
			UAST_ClassDefinition** owner = GetSymbolTable()->ClassNames.Find(it.Key());
			if (owner) owningClass = *owner;
			else owningClass = nullptr;

			// Analyse function body if it exists
			if (currentFunctionDefinition->Scope) currentFunctionDefinition->Scope->Analyse(this);
		}
	}
}


/*======================
 Variable definition
======================*/

void USAP_StaticAnalysis::Analyse(UAST_VariableDefinition* VariableDefinition)
{
	// Store this variable definition name as local variable
	LocalVariableNames.Add(VariableDefinition->Name);
}


/*======================
 Variable call
======================*/

void USAP_StaticAnalysis::Analyse(UAST_VariableCall* VariableCall)
{
	// Find static variable in class
	if (owningClass)
	{
		FStaticVariables* statVars = GetSymbolTable()->StaticVariables.Find(owningClass->Name);
		if (statVars)
		{
			for (UAST_VariableDefinition* varDef : statVars->Variables)
			{
				// Static variable definition found in class
				if (varDef->Name == VariableCall->VariableName) return;
			}
		}
	}

	// Find static variable in global scope
	FStaticVariables* statVars = GetSymbolTable()->StaticVariables.Find("");
	if (statVars)
	{
		for (UAST_VariableDefinition* varDef : statVars->Variables)
		{
			// Static variable definition found global scope
			if (varDef->Name == VariableCall->VariableName) return;
		}
	}

	// Find as local variable
	if (LocalVariableNames.Contains(VariableCall->VariableName)) return;

	// Find as a variable in top owner
	UAST_ClassDefinition* CurrentClass = GetSymbolTable()->ClassNames[GetSymbolTable()->TopOwner->Type];
	while (CurrentClass)
	{
		for (UAST_VariableDefinition* currentVarDef : CurrentClass->VariableDefinitions)
		{
			if (currentVarDef->Name == VariableCall->VariableName) return;
		}

		// Go to parent
		CurrentClass = GetSymbolTable()->ClassInheritance[CurrentClass];
	}


	ThrowError("Cannot call variable \"" + VariableCall->VariableName + "\" from inside a static function \""
		+ currentFunction->FunctionData.FunctionName + "\".");
}


/*======================
 Function call
======================*/

void USAP_StaticAnalysis::Analyse(UAST_FunctionCall* FunctionCall)
{
	// Find static function in class
	if (owningClass)
	{
		FStaticFunctions* statFun = GetSymbolTable()->StaticFunctions.Find(owningClass->Name);
		if (statFun)
		{
			for (UAST_FunctionDefinition* FunDef : statFun->Functions)
			{
				// Static function exists in class
				if (GetSymbolTable()->GetFunctionMatch(FunctionCall, FunDef->FunctionData.GetSignature(), "") != EFunctionMatching::NoMatch) return;
			}
		}
	}
	
	// Static function exists in global scope
	FStaticFunctions* statFun = GetSymbolTable()->StaticFunctions.Find("");
	if (statFun)
	{
		for (UAST_FunctionDefinition* FunDef : statFun->Functions)
		{
			// Static function exists in global scope
			if (GetSymbolTable()->GetFunctionMatch(FunctionCall, FunDef->FunctionData.GetSignature(), "") != EFunctionMatching::NoMatch) return;
		}
	}

	// Find as a function in top owner
	UAST_ClassDefinition* CurrentClass = GetSymbolTable()->ClassNames[GetSymbolTable()->TopOwner->Type];
	while (CurrentClass)
	{
		for (UAST_FunctionDefinition* CurrentFunDef : CurrentClass->FunctionDefinitions)
		{
			if (GetSymbolTable()->GetFunctionMatch(FunctionCall, CurrentFunDef->FunctionData.GetSignature(), "") != EFunctionMatching::NoMatch) return;
		}

		// Go to parent
		CurrentClass = GetSymbolTable()->ClassInheritance[CurrentClass];
	}

	// There is no static function that matches this call defined in either owning class or global scope.
	ThrowError("Cannot call function \"" + FunctionCall->FunctionName + "\" from inside a static function \""
		+ currentFunction->FunctionData.FunctionName + "\".");
}


/*======================
 Member access
======================*/

void USAP_StaticAnalysis::Analyse(UAST_MemberAccess* MemberAccess)
{
	// In member access we do not care about the callee.
	// Expression analysis passed, so we only need to check for caller.
	MemberAccess->lhs->Analyse(this);
}


