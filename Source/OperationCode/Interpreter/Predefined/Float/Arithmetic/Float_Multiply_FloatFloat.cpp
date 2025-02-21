// Fill out your copyright notice in the Description page of Project Settings.

#include "Float_Multiply_FloatFloat.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/FloatInstance.h"


UFloat_Multiply_FloatFloat::UFloat_Multiply_FloatFloat()
{
	FunctionData.FunctionName = "operator *";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "float";
	FunctionData.ParameterData.Add(FParameterData("float", "lhs", true, true, false));
	FunctionData.ParameterData.Add(FParameterData("float", "rhs", true, true, false));
}

UValue* UFloat_Multiply_FloatFloat::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	float lhs = RTS->GetFloatValue("lhs");
	float rhs = RTS->GetFloatValue("rhs");

	RTS->AddDebugMessage("Lhs has a value of " + FString::SanitizeFloat(lhs) + ", and rhs has a value of " + FString::SanitizeFloat(rhs) + ".");
	RTS->AddDebugMessage("Returning " + FString::SanitizeFloat(lhs * rhs) + ".");

	return URTS_InstanceCreator::CreateFloatValue(RTS->GetCodeRunner(), lhs * rhs);
}





