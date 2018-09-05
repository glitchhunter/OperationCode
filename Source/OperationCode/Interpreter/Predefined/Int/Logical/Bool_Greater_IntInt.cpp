// Fill out your copyright notice in the Description page of Project Settings.

#include "Bool_Greater_IntInt.h"

UBool_Greater_IntInt::UBool_Greater_IntInt()
{
	FunctionData.FunctionName = "operator >";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = false;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "bool";
	FunctionData.ParameterData.Add(FParameterData("int", "lhs", true, true, false));
	FunctionData.ParameterData.Add(FParameterData("int", "rhs", true, true, false));
}

UValue* UBool_Greater_IntInt::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	int32 lhs = RTS->GetIntValue("lhs");
	int32 rhs = RTS->GetIntValue("rhs");
	bool result = lhs > rhs;

	RTS->AddDebugMessage("Comparing lhs value " + FString::FromInt(lhs) + " with rhs value " + FString::FromInt(rhs) + " using operator >.");
	if (result) RTS->AddDebugMessage("Lhs is greater then rhs, returning true.");
	else RTS->AddDebugMessage("Lhs is not greater then rhs, returning false.");

	return URTS_InstanceCreator::CreateBoolValue(RTS->GetCodeRunner(), result);
}




