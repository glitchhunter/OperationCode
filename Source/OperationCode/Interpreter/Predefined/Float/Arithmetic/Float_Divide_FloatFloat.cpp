// Fill out your copyright notice in the Description page of Project Settings.

#include "Float_Divide_FloatFloat.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/FloatInstance.h"


UFloat_Divide_FloatFloat::UFloat_Divide_FloatFloat()
{
	FunctionData.FunctionName = "operator /";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = false;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "float";
	FunctionData.ParameterData.Add(FParameterData("float", "lhs", true, true, false));
	FunctionData.ParameterData.Add(FParameterData("float", "rhs", true, true, false));
}

UValue* UFloat_Divide_FloatFloat::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	float lhs = RTS->GetFloatValue("lhs");
	float rhs = RTS->GetFloatValue("rhs");

	// Throw runtime error if we divide by 0
	if (rhs == 0.0f)
	{
		RTS->ThrowRuntimeError("Division by 0 detected. (" + FString::SanitizeFloat(lhs) + "/0).");
		return URTS_InstanceCreator::CreateFloatValue(RTS->GetCodeRunner(), 0);
	}

	RTS->AddDebugMessage("Lhs has a value of " + FString::SanitizeFloat(lhs) + ", and rhs has a value of " + FString::SanitizeFloat(rhs) + ".");
	RTS->AddDebugMessage("Returning " + FString::SanitizeFloat(lhs / rhs) + ".");

	return URTS_InstanceCreator::CreateFloatValue(RTS->GetCodeRunner(), lhs / rhs);
}




