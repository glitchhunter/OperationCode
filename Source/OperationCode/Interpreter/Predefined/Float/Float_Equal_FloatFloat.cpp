// Fill out your copyright notice in the Description page of Project Settings.

#include "Float_Equal_FloatFloat.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/FloatInstance.h"

UFloat_Equal_FloatFloat::UFloat_Equal_FloatFloat()
{
	FunctionData.FunctionName = "operator =";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "float";
	FunctionData.ParameterData.Add(FParameterData("float", "lhs", true, false, false));
	FunctionData.ParameterData.Add(FParameterData("float", "rhs", true, true, false));
}

UValue* UFloat_Equal_FloatFloat::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	UFloatInstance* lhs = RTS->GetFloatVariable("lhs");
	float rhs = RTS->GetFloatValue("rhs");

	RTS->AddDebugMessage("Storing rhs value " + FString::SanitizeFloat(rhs) + " into lhs.");
	lhs->Value = rhs;
	return lhs;
}



