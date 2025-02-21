// Fill out your copyright notice in the Description page of Project Settings.

#include "Int_OperatorModulo_IntInt.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/IntInstance.h"

UInt_OperatorModulo_IntInt::UInt_OperatorModulo_IntInt()
{
	FunctionData.FunctionName = "operator %";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "int";
	FunctionData.ParameterData.Add(FParameterData("int", "lhs", true, true, false));
	FunctionData.ParameterData.Add(FParameterData("int", "rhs", true, true, false));
}

UValue* UInt_OperatorModulo_IntInt::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	int32 lhs = RTS->GetIntValue("lhs");
	int32 rhs = RTS->GetIntValue("rhs");

	// Check for modulo 0
	if (rhs == 0)
	{
		RTS->ThrowRuntimeError("Cannot modulo by 0");
		return URTS_InstanceCreator::CreateIntValue(RTS->GetCodeRunner(), 0);
	}

	int32 result = lhs % rhs;

	RTS->AddDebugMessage("Taking the modulo of lhs value " + FString::FromInt(lhs) + " and rhs value " + FString::FromInt(rhs) + ".");
	RTS->AddDebugMessage("Returning the values of " + FString::FromInt(result) + ".");

	return URTS_InstanceCreator::CreateIntValue(RTS->GetCodeRunner(), result);
}



