// Fill out your copyright notice in the Description page of Project Settings.

#include "Value.h"
#include "Interpreter/CodeRunner/CodeRunner.h"
#include "Interpreter/Parser/AST/Definition/AST_ClassDefinition.h"
#include "Interpreter/Parser/AST/Definition/AST_VariableDefinition.h"
#include "Interpreter/SemanticAnalysis/SymbolTable.h"

UValue* UValue::GetVariable(FString	VarName)
{
	UValue** val = Variables->Variables.Find(VarName);
	if (!val)
	{
		return nullptr;
	}

	return *val;
}

void UValue::Init(FString ValueType, UCodeRunner* codeRunner)
{
	CodeRunner = codeRunner;
	Type = ValueType;
	ChachedIsNullable = CodeRunner->GetSymbolTable()->IsInstanceUniqueByName(Type);
}

void UValue::CreateVariables()
{
	Variables = NewObject<UVariables>(this);
}

UValue* UValue::Duplicate_Implementation()
{
	UValue* duplicate = NewObject<UValue>(CodeRunner);
	duplicate->Init(Type, CodeRunner);
	if (IsNullable())
		duplicate->Variables = Variables;
	else
	{
		duplicate->CreateVariables();
		for (auto it = Variables->Variables.CreateConstIterator(); it; ++it)
		{
			duplicate->Variables->Variables.Add(it.Key(), it.Value()->Duplicate());
		}
		//TMap<FString, UValue*> Vars = TMap<FString, UValue*>(Variables->Variables);
		//duplicate->Variables->Variables = Vars;
	}

	return duplicate;
}

