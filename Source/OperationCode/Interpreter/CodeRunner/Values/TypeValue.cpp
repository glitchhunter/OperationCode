// Fill out your copyright notice in the Description page of Project Settings.

#include "TypeValue.h"
#include "Interpreter/Parser/AST/Definition/AST_VariableDefinition.h"
#include "Interpreter/SemanticAnalysis/SymbolTable.h"


void UTypeValue::Init(FString ValueType, UCodeRunner* codeRunner)
{
	CodeRunner = codeRunner;
	Type = ValueType;
	CreateVariables();
}


