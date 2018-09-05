// Fill out your copyright notice in the Description page of Project Settings.

#include "String_ConvertAuto_Bool.h"

UString_ConvertAuto_Bool::UString_ConvertAuto_Bool()
{
	FunctionData.FunctionName = "convert auto string";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = false;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "string";
	FunctionData.ParameterData.Add(FParameterData("bool", "val", true, true, false));
}

UValue* UString_ConvertAuto_Bool::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	bool val = RTS->GetBoolValue("val");
	FString ValAsString = val ? "true" : "false";

	RTS->AddDebugMessage("Implicitly converting bool value to string with value " + ValAsString + ".");
	return URTS_InstanceCreator::CreateStringValue(RTS->GetCodeRunner(), ValAsString);
}




