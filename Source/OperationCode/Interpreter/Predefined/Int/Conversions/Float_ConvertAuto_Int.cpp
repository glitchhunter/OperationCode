// Fill out your copyright notice in the Description page of Project Settings.

#include "Float_ConvertAuto_Int.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/FloatInstance.h"

UFloat_ConvertAuto_Int::UFloat_ConvertAuto_Int()
{
	FunctionData.FunctionName = "convert auto float";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "float";
	FunctionData.ParameterData.Add(FParameterData("int", "val", true, true, false));
}

UValue* UFloat_ConvertAuto_Int::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	int32 val = RTS->GetIntValue("val");
	float result = val;

	RTS->AddDebugMessage("Implicitly converting int value to float with value " + FString::SanitizeFloat(result) + ".");
	return URTS_InstanceCreator::CreateFloatValue(RTS->GetCodeRunner(), result);
}




