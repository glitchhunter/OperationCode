// Fill out your copyright notice in the Description page of Project Settings.

#include "Bool_ConvertAuto_Int.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/BoolInstance.h"

UBool_ConvertAuto_Int::UBool_ConvertAuto_Int()
{
	FunctionData.FunctionName = "convert auto bool";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "bool";
	FunctionData.ParameterData.Add(FParameterData("int", "val", true, true, false));
}

UValue* UBool_ConvertAuto_Int::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	int32 val = RTS->GetIntValue("val");
	bool result = val != 0;
	FString StringResult = result ? "true" : "false";
	RTS->AddDebugMessage("Implicitly converting int value to bool with value " + StringResult + ".");
	return URTS_InstanceCreator::CreateBoolValue(RTS->GetCodeRunner(), result);
}




