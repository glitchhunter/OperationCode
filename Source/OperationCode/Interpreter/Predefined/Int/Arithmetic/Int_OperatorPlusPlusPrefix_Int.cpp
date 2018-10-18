// Fill out your copyright notice in the Description page of Project Settings.

#include "Int_OperatorPlusPlusPrefix_Int.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/IntInstance.h"

UInt_OperatorPlusPlusPrefix_Int::UInt_OperatorPlusPlusPrefix_Int()
{
	FunctionData.FunctionName = "operator ++ (prefix)";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = true;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "int";
	FunctionData.ParameterData.Add(FParameterData("int", "val", true, false, false));
}

UValue* UInt_OperatorPlusPlusPrefix_Int::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	UIntInstance* val = RTS->GetIntVariable("val");
	RTS->AddDebugMessage("Incrementing the given value " + FString::FromInt(val->Value) + " and returning it.");
	val->Value += 1;
	return val;
}



