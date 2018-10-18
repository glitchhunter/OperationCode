// Fill out your copyright notice in the Description page of Project Settings.

#include "Bool_Less_IntInt.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/BoolInstance.h"

UBool_Less_IntInt::UBool_Less_IntInt()
{
	FunctionData.FunctionName = "operator <";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "bool";
	FunctionData.ParameterData.Add(FParameterData("int", "lhs", true, true, false));
	FunctionData.ParameterData.Add(FParameterData("int", "rhs", true, true, false));
}

UValue* UBool_Less_IntInt::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	int32 lhs = RTS->GetIntValue("lhs");
	int32 rhs = RTS->GetIntValue("rhs");
	bool result = lhs < rhs;

	RTS->AddDebugMessage("Comparing lhs value " + FString::FromInt(lhs) + " with rhs value " + FString::FromInt(rhs) + " using operator <.");
	if (result) RTS->AddDebugMessage("Lhs is smaller then rhs, returning true.");
	else RTS->AddDebugMessage("Lhs is not smaller then rhs, returning false.");

	return URTS_InstanceCreator::CreateBoolValue(RTS->GetCodeRunner(), result);
}




