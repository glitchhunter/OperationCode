// Fill out your copyright notice in the Description page of Project Settings.

#include "String_ConvertAuto_Float.h"

UString_ConvertAuto_Float::UString_ConvertAuto_Float()
{
	FunctionData.FunctionName = "convert auto string";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = false;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "string";
	FunctionData.ParameterData.Add(FParameterData("float", "val", true, true, false));
}

UValue* UString_ConvertAuto_Float::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	float val = RTS->GetFloatValue("val");
	FString ValAsString = FString::SanitizeFloat(val);

	RTS->AddDebugMessage("Implicitly converting float value to string with value " + ValAsString + ".");
	return URTS_InstanceCreator::CreateStringValue(RTS->GetCodeRunner(), ValAsString);
}




