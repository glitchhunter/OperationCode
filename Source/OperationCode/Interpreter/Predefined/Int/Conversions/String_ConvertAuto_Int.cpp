// Fill out your copyright notice in the Description page of Project Settings.

#include "String_ConvertAuto_Int.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/StringInstance.h"

UString_ConvertAuto_Int::UString_ConvertAuto_Int()
{
	FunctionData.FunctionName = "convert auto string";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "string";
	FunctionData.ParameterData.Add(FParameterData("int", "val", true, true, false));
}

UValue* UString_ConvertAuto_Int::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	int32 val = RTS->GetIntValue("val");
	FString result = FString::FromInt(val);

	RTS->AddDebugMessage("Implicitly converting int value to string with value " + result + ".");
	return URTS_InstanceCreator::CreateStringValue(RTS->GetCodeRunner(), result);
}




