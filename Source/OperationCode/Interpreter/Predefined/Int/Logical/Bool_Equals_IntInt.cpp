// Fill out your copyright notice in the Description page of Project Settings.

#include "Bool_Equals_IntInt.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/BoolInstance.h"

UBool_Equals_IntInt::UBool_Equals_IntInt()
{
	FunctionData.FunctionName = "operator ==";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "bool";
	FunctionData.ParameterData.Add(FParameterData("int", "lhs", true, true, false));
	FunctionData.ParameterData.Add(FParameterData("int", "rhs", true, true, false));
}

UValue* UBool_Equals_IntInt::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	int32 lhs = RTS->GetIntValue("lhs");
	int32 rhs = RTS->GetIntValue("rhs");
	bool result = lhs == rhs;

	RTS->AddDebugMessage("Comparing lhs value " + FString::FromInt(lhs) + " with rhs value " + FString::FromInt(rhs) + " using operator ==.");
	if (result) RTS->AddDebugMessage("Values are equal, returning true.");
	else RTS->AddDebugMessage("Values are different, returning false.");

	return URTS_InstanceCreator::CreateBoolValue(RTS->GetCodeRunner(), result);
}


