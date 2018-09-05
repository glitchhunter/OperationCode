// Fill out your copyright notice in the Description page of Project Settings.

#include "SAP_StoreStatics.h"
#include "Interpreter/SemanticAnalysis/SymbolTable.h"



void USAP_StoreStatics::AddStaticFunction(UAST_FunctionDefinition* FunctionDefinition, FString className)
{
	GetSymbolTable()->StaticFunctions.FindOrAdd(className).Functions.Add(FunctionDefinition);
}

void USAP_StoreStatics::AddStaticVariable(UAST_VariableDefinition* VariableDefinition, FString className)
{
	GetSymbolTable()->StaticVariables.FindOrAdd(className).Variables.Add(VariableDefinition);
}

void USAP_StoreStatics::DefaultBehaviour(UAST_Node* Node)
{
	CurrentScope = ECurrentScope::Local;
	AnalyseChildren(Node);
}


/*======================
 Basic
======================*/

void USAP_StoreStatics::Analyse(UAST_Basic* Basic)
{
	for (UAST_Node* currentChild : Basic->GetChildren())
	{
		CurrentScope = ECurrentScope::Global;
		currentChild->Analyse(this);
	}
}


/*======================
 Main
======================*/

void USAP_StoreStatics::Analyse(UAST_Main* Main)
{
	for (UAST_Node* currentChild : Main->GetChildren())
	{
		CurrentScope = ECurrentScope::Global;
		currentChild->Analyse(this);
	}
}


/*======================
 Class definition
======================*/

void USAP_StoreStatics::Analyse(UAST_ClassDefinition* ClassDefinition)
{
	for (UAST_Node* currentChild : ClassDefinition->GetChildren())
	{
		CurrentScope = ECurrentScope::InClass;
		CurrentClass = ClassDefinition;
		currentChild->Analyse(this);
	}
}


/*======================
 Function definition
======================*/

void USAP_StoreStatics::Analyse(UAST_FunctionDefinition* FunctionDefinition)
{
	switch (CurrentScope)
	{
		// Function is defined in globas scope
	case ECurrentScope::Global:
		FunctionDefinition->FunctionData.IsStatic = true;
		AddStaticFunction(FunctionDefinition, "");
		break;

		// Function exists in currentClass
	case ECurrentScope::InClass:
		if (FunctionDefinition->FunctionData.IsStatic)
			AddStaticFunction(FunctionDefinition, CurrentClass->Name);
		break;

		// Function can only be declared inside a class or global scope
	case ECurrentScope::Local:
		break;

	default:
		break;
	}

	CurrentScope = ECurrentScope::Local;

	// Scope can be nullptr if the function is predefined
	if (FunctionDefinition->Scope) FunctionDefinition->Scope->Analyse(this);
}


/*======================
 Variable definition
======================*/

void USAP_StoreStatics::Analyse(UAST_VariableDefinition* VariableDefinition)
{
	switch (CurrentScope)
	{
		// Variable is defined in global scope
	case ECurrentScope::Global:
		VariableDefinition->IsStatic = true;
		AddStaticVariable(VariableDefinition, "");
		break;

		// Variable is defined in class
	case ECurrentScope::InClass:
		if (VariableDefinition->IsStatic)
			AddStaticVariable(VariableDefinition, CurrentClass->Name);
		break;

		// Variable is defined localy, therefore it cannot be static
	case ECurrentScope::Local:
		if (VariableDefinition->IsStatic)
		{
			ThrowError("Variable " + VariableDefinition->Name + " is local but is defined as static.");
		}
		break;

	default:
		break;
	}
}


