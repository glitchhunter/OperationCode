// Fill out your copyright notice in the Description page of Project Settings.

#include "Int_OperatorDivide_IntInt.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/IntInstance.h"

UInt_OperatorDivide_IntInt::UInt_OperatorDivide_IntInt()
{
	FunctionData.FunctionName = "operator /";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "int";
	FunctionData.ParameterData.Add(FParameterData("int", "lhs", true, true, false));
	FunctionData.ParameterData.Add(FParameterData("int", "rhs", true, true, false));
}

UValue* UInt_OperatorDivide_IntInt::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	int32 lhs = RTS->GetIntValue("lhs");
	int32 rhs = RTS->GetIntValue("rhs");

	// Throw runtime error if we divide by 0
	if (rhs == 0)
	{
		RTS->ThrowRuntimeError("Division by 0 detected. (" + FString::FromInt(lhs) + "/0).");
		return URTS_InstanceCreator::CreateIntValue(RTS->GetCodeRunner(), 0);
	}

	int32 result = lhs / rhs;

	RTS->AddDebugMessage("Dividing lhs value " + FString::FromInt(lhs) + " with rhs value " + FString::FromInt(rhs) + ".");
	RTS->AddDebugMessage("Returning the values of " + FString::FromInt(result) + ".");
	
	return URTS_InstanceCreator::CreateIntValue(RTS->GetCodeRunner(), result);
}




