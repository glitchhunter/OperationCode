// Fill out your copyright notice in the Description page of Project Settings.

#include "UnaryPlus_Int.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/IntInstance.h"

UUnaryPlus_Int::UUnaryPlus_Int()
{
	FunctionData.FunctionName = "operator +";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = false;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "int";
	FunctionData.ParameterData.Add(FParameterData("int", "value", true, true, false));
}

UValue* UUnaryPlus_Int::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	int32 value = RTS->GetIntValue("value");

	RTS->AddDebugMessage("Returning the value of " + FString::FromInt(value) + ".");

	return URTS_InstanceCreator::CreateIntValue(RTS->GetCodeRunner(), value);
}



