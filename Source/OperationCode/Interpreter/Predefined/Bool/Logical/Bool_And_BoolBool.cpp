// Fill out your copyright notice in the Description page of Project Settings.

#include "Bool_And_BoolBool.h"

UBool_And_BoolBool::UBool_And_BoolBool()
{
	FunctionData.FunctionName = "operator &&";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = false;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "bool";
	FunctionData.ParameterData.Add(FParameterData("bool", "lhs", true, true, false));
	FunctionData.ParameterData.Add(FParameterData("bool", "rhs", true, true, false));
}

UValue* UBool_And_BoolBool::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	bool lhs = RTS->GetBoolValue("lhs");
	if (!lhs)
	{
		RTS->AddDebugMessage("Lhs is false, returning false.");
		return URTS_InstanceCreator::CreateBoolValue(RTS->GetCodeRunner(), false);
	}

	bool rhs = RTS->GetBoolValue("rhs");
	if (!rhs)
	{
		RTS->AddDebugMessage("Lhs is true, but rhs is false. Returning false");
		return URTS_InstanceCreator::CreateBoolValue(RTS->GetCodeRunner(), false);
	}

	RTS->AddDebugMessage("Both lhs and rhs are true. Returning true.");
	return URTS_InstanceCreator::CreateBoolValue(RTS->GetCodeRunner(), true);
}



