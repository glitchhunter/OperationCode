// Fill out your copyright notice in the Description page of Project Settings.

#include "UnaryMinus_Float.h"
#include "Interpreter/CodeRunner/RuntimeStates/Implicit/RTS_InstanceCreator.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/FloatInstance.h"


UUnaryMinus_Float::UUnaryMinus_Float()
{
	FunctionData.FunctionName = "operator -";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "float";
	FunctionData.ParameterData.Add(FParameterData("float", "value", true, true, false));
}

UValue* UUnaryMinus_Float::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	float value = RTS->GetFloatValue("value");

	RTS->AddDebugMessage("Float has a value of " + FString::SanitizeFloat(value));
	RTS->AddDebugMessage("Returning " + FString::SanitizeFloat(-value) + ".");

	return URTS_InstanceCreator::CreateFloatValue(RTS->GetCodeRunner(), -value);
}





