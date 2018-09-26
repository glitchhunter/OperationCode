// Fill out your copyright notice in the Description page of Project Settings.

#include "SimpleFunctionDefinitionRTS.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"



void USimpleFunctionDefinitionRTS::RunStep()
{
	UValue* returnedValue = SimpleFunction->Run(this);
	GetCodeRunner()->PopStackFrame();
	GetCodeRunner()->SetValue(returnedValue);
	Finished();
}

UAST_Node* USimpleFunctionDefinitionRTS::GetNode() const
{
	return SimpleFunction;
}

void USimpleFunctionDefinitionRTS::SetPredefinedFunctionDefinition(USimplePredefinedFunction* simpleFunction)
{
	SimpleFunction = simpleFunction;
	FunctionDefinition = SimpleFunction;
}




