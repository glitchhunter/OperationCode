// Fill out your copyright notice in the Description page of Project Settings.

#include "Bool_Equal_BoolBool.h"


UBool_Equal_BoolBool::UBool_Equal_BoolBool()
{
	FunctionData.FunctionName = "operator =";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = false;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "bool";
	FunctionData.ParameterData.Add(FParameterData("bool", "lhs", true, false, false));
	FunctionData.ParameterData.Add(FParameterData("bool", "rhs", true, true, false));
}

UValue* UBool_Equal_BoolBool::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	UBoolInstance* lhs = RTS->GetBoolVariable("lhs");
	bool rhs = RTS->GetBoolValue("rhs");
	FString boolString = rhs ? "true" : "false";
	RTS->AddDebugMessage("Storing " + boolString + " in lhs.");
	return lhs;
}

