// Fill out your copyright notice in the Description page of Project Settings.

#include "String_Equal_StringString.h"

UString_Equal_StringString::UString_Equal_StringString()
{
	FunctionData.FunctionName = "operator =";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = false;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "string";
	FunctionData.ParameterData.Add(FParameterData("string", "lhs", true, false, false));
	FunctionData.ParameterData.Add(FParameterData("string", "rhs", true, true, false));
}

UValue* UString_Equal_StringString::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	UStringInstance* lhs = RTS->GetStringVariable("lhs");
	FString rhs = RTS->GetStringValue("rhs");

	RTS->AddDebugMessage("Storing rhs values " + rhs + " int lhs.");
	lhs->Value = rhs;
	return lhs;
}



