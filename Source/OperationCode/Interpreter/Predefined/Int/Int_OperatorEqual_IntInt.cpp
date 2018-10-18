// Fill out your copyright notice in the Description page of Project Settings.

#include "Int_OperatorEqual_IntInt.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/IntInstance.h"

UInt_OperatorEqual_IntInt::UInt_OperatorEqual_IntInt()
{
	FunctionData.FunctionName = "operator =";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = true;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "int";
	FunctionData.ParameterData.Add(FParameterData("int", "lhs", true, false, false));
	FunctionData.ParameterData.Add(FParameterData("int", "rhs", true, true, false));
}

UValue* UInt_OperatorEqual_IntInt::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	int32 rhs = RTS->GetIntValue("rhs");
	UIntInstance* lhs = RTS->GetIntVariable("lhs");
	lhs->Value = rhs;
	RTS->AddDebugMessage("Storing the int value of " + FString::FromInt(rhs) + " in lhs variable.");
	return lhs;
}



