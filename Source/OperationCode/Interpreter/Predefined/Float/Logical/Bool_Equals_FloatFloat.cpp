// Fill out your copyright notice in the Description page of Project Settings.

#include "Bool_Equals_FloatFloat.h"


UBool_Equals_FloatFloat::UBool_Equals_FloatFloat()
{
	FunctionData.FunctionName = "operator ==";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = false;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "bool";
	FunctionData.ParameterData.Add(FParameterData("float", "lhs", true, true, false));
	FunctionData.ParameterData.Add(FParameterData("float", "rhs", true, true, false));
}

UValue* UBool_Equals_FloatFloat::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	float lhs = RTS->GetFloatValue("lhs");
	float rhs = RTS->GetFloatValue("rhs");

	RTS->AddDebugMessage("Lhs has a value of " + FString::SanitizeFloat(lhs) + ", and rhs has a value of " + FString::SanitizeFloat(rhs) + ".");
	RTS->AddDebugMessage("Friendly reminder to never directly compare float values.");
	if (lhs == rhs)
	{
		RTS->AddDebugMessage("Lhs has the same value as rhs. Returning true.");
		return URTS_InstanceCreator::CreateBoolValue(RTS->GetCodeRunner(), true);
	}

	RTS->AddDebugMessage("Lhs does not have the same value as rhs. This could be a floating point error. Returning false.");
	return URTS_InstanceCreator::CreateBoolValue(RTS->GetCodeRunner(), false);
}





