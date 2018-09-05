// Fill out your copyright notice in the Description page of Project Settings.

#include "SAP_ClassAnalysis.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/SemanticAnalysis/SymbolTable.h"

#include "Interpreter/Parser/AST/AST_Basic.h"
#include "Interpreter/Parser/AST/AST_Main.h"

#include "Interpreter/Parser/AST/Definition/AST_ClassDefinition.h"
#include "Interpreter/Parser/AST/Definition/AST_FunctionDefinition.h"

#include "Interpreter/SemanticAnalysis/SemanticAnalysis.h"


void USAP_ClassAnalysis::StartAnalysis(UAST_Node* RootNode)
{
	Super::StartAnalysis(RootNode);

	if (HasErrors()) return;
	StoreChildParentRelationships();

	if (HasErrors()) return;
	CheckForCircularDependency();
}

/*======================
 Basic
======================*/

void USAP_ClassAnalysis::Analyse(UAST_Basic* Basic)
{
	AnalyseChildren(Basic);

	UValue* TopOwner = GetSymbolTable()->TopOwner;
	if (!TopOwner) return;

	if (!GetSymbolTable()->ClassNames.Contains(TopOwner->Type))
		ThrowError("Top owner is of unknownt type " + TopOwner->Type + ".");
}

/*======================
 Main
======================*/

void USAP_ClassAnalysis::Analyse(UAST_Main* Main)
{
	AnalyseChildren(Main);
}


/*======================
 Class definition
======================*/

void USAP_ClassAnalysis::Analyse(UAST_ClassDefinition* ClassDefinition)
{
	// Check if class with same name has already been found
	if (GetSymbolTable()->ClassNames.Contains(ClassDefinition->Name))
	{
		ThrowError(TEXT("Duplicate class " + ClassDefinition->Name + " Detected."));
		return;
	}

	GetSymbolTable()->ClassNames.Add(ClassDefinition->Name, ClassDefinition);
}






void USAP_ClassAnalysis::StoreChildParentRelationships()
{
	// Loop through every class
	for (TMap<FString, UAST_ClassDefinition*>::TConstIterator it = GetSymbolTable()->ClassNames.CreateConstIterator(); it; ++it)
	{
		FString ParentName = it->Value->ParentName;

		// If this class has no paprent
		if (ParentName == "")
		{
			// nullptr as parent means this is base class
			GetSymbolTable()->ClassInheritance.Add(it->Value, nullptr);
			continue;
		}

		// Check if class with ParentName exists
		UAST_ClassDefinition** parent = GetSymbolTable()->ClassNames.Find(ParentName);
		if (!parent)
		{
			ThrowError("Class \"" + it->Value->Name + "\" inherits from unknown class \"" + ParentName + "\".");
			return;
		}

		// Store child parent relationship
		GetSymbolTable()->ClassInheritance.Add(it->Value, *parent);
	}
}

void USAP_ClassAnalysis::CheckForCircularDependency()
{
	// Set of all the visited classes. If a class is revisited, then there is a circular dependency
	TSet<UAST_ClassDefinition*> VisitedClasses;

	// Loop through every class
	for (TMap<FString, UAST_ClassDefinition*>::TConstIterator it = GetSymbolTable()->ClassNames.CreateConstIterator(); it; ++it)
	{
		UAST_ClassDefinition* currentClass = it->Value;
		TSet<UAST_ClassDefinition*> visitedChain;

		// If this class has been visited, then we already checked this inheritance chain
		if (VisitedClasses.Contains(currentClass)) continue;

		// Go to parent
		currentClass = GetSymbolTable()->ClassInheritance[currentClass];

		// Loop through children
		while (currentClass)
		{
			// If this class has been visited, then there is a cyclic dependency
			if (visitedChain.Contains(currentClass))
			{
				ThrowError("Circular dependency detected with class \"" + currentClass->Name + "\".");
				return;
			}
			// mark this class as visited
			VisitedClasses.Add(currentClass);
			visitedChain.Add(currentClass);

			// Go to next class
			currentClass = GetSymbolTable()->ClassInheritance[currentClass];
		}
	}

}


