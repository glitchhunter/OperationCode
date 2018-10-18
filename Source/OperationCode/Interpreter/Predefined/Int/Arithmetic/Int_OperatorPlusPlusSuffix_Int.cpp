// Fill out your copyright notice in the Description page of Project Settings.

#include "Int_OperatorPlusPlusSuffix_Int.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/IntInstance.h"

UInt_OperatorPlusPlusSuffix_Int::UInt_OperatorPlusPlusSuffix_Int()
{
	FunctionData.FunctionName = "operator ++ (suffix)";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "int";
	FunctionData.ParameterData.Add(FParameterData("int", "val", true, false, false));
}

UValue* UInt_OperatorPlusPlusSuffix_Int::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	UIntInstance* val = RTS->GetIntVariable("val");
	RTS->AddDebugMessage("Incrementing val and returning the pre-incremented value " + FString::FromInt(val->Value) + ".");
	UIntInstance* copy = URTS_InstanceCreator::CreateIntValue(RTS->GetCodeRunner(), val->Value);
	val->Value += 1;
	return copy;
}



