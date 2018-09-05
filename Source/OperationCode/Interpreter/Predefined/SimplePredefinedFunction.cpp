// Fill out your copyright notice in the Description page of Project Settings.

#include "SimplePredefinedFunction.h"
#include "Interpreter/Predefined/SimpleFunctionDefinitionRTS.h"


URuntimeState* USimplePredefinedFunction::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	USimpleFunctionDefinitionRTS* SFD = NewObject<USimpleFunctionDefinitionRTS>(CodeRunner);
	SFD->Init(CodeRunner);
	SFD->SetPredefinedFunctionDefinition(this);
	return SFD;
}

UValue* USimplePredefinedFunction::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	return nullptr;
}
