// Fill out your copyright notice in the Description page of Project Settings.

#include "Int_OperatorPlus_IntInt.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/IntInstance.h"

UInt_OperatorPlus_IntInt::UInt_OperatorPlus_IntInt()
{
	FunctionData.FunctionName = "operator +";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "int";
	FunctionData.ParameterData.Add(FParameterData("int", "lhs", true, true, false));
	FunctionData.ParameterData.Add(FParameterData("int", "rhs", true, true, false));
}

UValue* UInt_OperatorPlus_IntInt::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	int32 lhs = RTS->GetIntValue("lhs");
	int32 rhs = RTS->GetIntValue("rhs");
	int32 result = lhs + rhs;

	RTS->AddDebugMessage("Adding lhs value " + FString::FromInt(lhs) + " with rhs value " + FString::FromInt(rhs) + ".");
	RTS->AddDebugMessage("Returning the value of " + FString::FromInt(result) + ".");

	return URTS_InstanceCreator::CreateIntValue(RTS->GetCodeRunner(), result);
}



