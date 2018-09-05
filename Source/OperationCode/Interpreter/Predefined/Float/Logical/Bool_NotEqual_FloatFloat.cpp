// Fill out your copyright notice in the Description page of Project Settings.

#include "Bool_NotEqual_FloatFloat.h"

UBool_NotEqual_FloatFloat::UBool_NotEqual_FloatFloat()
{
	FunctionData.FunctionName = "operator !=";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = false;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "bool";
	FunctionData.ParameterData.Add(FParameterData("float", "lhs", true, true, false));
	FunctionData.ParameterData.Add(FParameterData("float", "rhs", true, true, false));
}

UValue* UBool_NotEqual_FloatFloat::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	float lhs = RTS->GetFloatValue("lhs");
	float rhs = RTS->GetFloatValue("rhs");

	RTS->AddDebugMessage("Lhs has a value of " + FString::SanitizeFloat(lhs) + ", and rhs has a value of " + FString::SanitizeFloat(rhs) + ".");
	if (lhs != rhs)
	{
		RTS->AddDebugMessage("Lhs has a value different value then rhs. Returning true.");
		return URTS_InstanceCreator::CreateBoolValue(RTS->GetCodeRunner(), true);
	}

	RTS->AddDebugMessage("Lhs does not have a different value then rhs. Returning false.");
	return URTS_InstanceCreator::CreateBoolValue(RTS->GetCodeRunner(), false);
}



