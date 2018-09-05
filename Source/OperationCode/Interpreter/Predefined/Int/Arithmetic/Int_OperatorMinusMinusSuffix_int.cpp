// Fill out your copyright notice in the Description page of Project Settings.

#include "Int_OperatorMinusMinusSuffix_int.h"

UInt_OperatorMinusMinusSuffix_int::UInt_OperatorMinusMinusSuffix_int()
{
	FunctionData.FunctionName = "operator -- (suffix)";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = false;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "int";
	FunctionData.ParameterData.Add(FParameterData("int", "val", true, false, false));
}

UValue* UInt_OperatorMinusMinusSuffix_int::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	UIntInstance* val = RTS->GetIntVariable("val");
	RTS->AddDebugMessage("Decrementing val and returning the pre-decremented value " + FString::FromInt(val->Value) + ".");
	UIntInstance* copy = URTS_InstanceCreator::CreateIntValue(RTS->GetCodeRunner(), val->Value);
	val->Value -= 1;
	return copy;
}



