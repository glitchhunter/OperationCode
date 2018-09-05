// Fill out your copyright notice in the Description page of Project Settings.

#include "Bool_NotEqualNoCase_StringString.h"

UBool_NotEqualNoCase_StringString::UBool_NotEqualNoCase_StringString()
{
	FunctionData.FunctionName = "NotEqualIgnoreCase";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = false;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "bool";
	FunctionData.ParameterData.Add(FParameterData("string", "lhs", true, true, false));
	FunctionData.ParameterData.Add(FParameterData("string", "rhs", true, true, false));
}

UValue* UBool_NotEqualNoCase_StringString::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	FString lhs = RTS->GetStringValue("lhs");
	FString rhs = RTS->GetStringValue("rhs");
	bool result = lhs.Equals(rhs, ESearchCase::IgnoreCase);

	RTS->AddDebugMessage("Comparing lhs value " + lhs + " with rhs value " + rhs + " ignoring case.");
	if (result) RTS->AddDebugMessage("Lhs value contains a different string from rhs value, returning true.");
	else RTS->AddDebugMessage("Lhs value does not contain a different string from rhs value, returning false.");

	return URTS_InstanceCreator::CreateBoolValue(RTS->GetCodeRunner(), result);
}



