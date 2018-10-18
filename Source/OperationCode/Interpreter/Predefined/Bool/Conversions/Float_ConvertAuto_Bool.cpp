// Fill out your copyright notice in the Description page of Project Settings.

#include "Float_ConvertAuto_Bool.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/FloatInstance.h"

UFloat_ConvertAuto_Bool::UFloat_ConvertAuto_Bool()
{
	FunctionData.FunctionName = "convert auto float";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "float";
	FunctionData.ParameterData.Add(FParameterData("bool", "val", true, true, false));
}

UValue* UFloat_ConvertAuto_Bool::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	float val = RTS->GetFloatValue("val");

	RTS->AddDebugMessage("Implicitly converting bool value to float with value " + FString::SanitizeFloat(val) + ".");
	return URTS_InstanceCreator::CreateFloatValue(RTS->GetCodeRunner(), val);
}




