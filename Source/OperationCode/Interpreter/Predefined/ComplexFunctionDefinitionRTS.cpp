// Fill out your copyright notice in the Description page of Project Settings.

#include "ComplexFunctionDefinitionRTS.h"
#include "Interpreter/Predefined/ComplexPredefinedFunction.h"



void UComplexFunctionDefinitionRTS::RunStep()
{
	RunStep_BP();
}

UAST_Node* UComplexFunctionDefinitionRTS::GetNode() const
{
	return ComplexFunctionDefinition;
}

void UComplexFunctionDefinitionRTS::Finished_BP(UValue* returnValue)
{
	GetCodeRunner()->PopStackFrame();
	GetCodeRunner()->SetValue(returnValue);
	Finished();
}
