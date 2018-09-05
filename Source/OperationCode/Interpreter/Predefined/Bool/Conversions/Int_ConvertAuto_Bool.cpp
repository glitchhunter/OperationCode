// Fill out your copyright notice in the Description page of Project Settings.

#include "Int_ConvertAuto_Bool.h"

UInt_ConvertAuto_Bool::UInt_ConvertAuto_Bool()
{
	FunctionData.FunctionName = "convert auto int";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = false;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "int";
	FunctionData.ParameterData.Add(FParameterData("bool", "val", true, true, false));
}

UValue* UInt_ConvertAuto_Bool::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	int32 val = RTS->GetIntValue("val");

	RTS->AddDebugMessage("Implicitly converting bool value to int with value " + FString::FromInt(val) + ".");
	return URTS_InstanceCreator::CreateIntValue(RTS->GetCodeRunner(), val);
}



