// Fill out your copyright notice in the Description page of Project Settings.

#include "Array_OperatorEqual_ArrayArray.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/ArrayInstance.h"


UArray_OperatorEqual_ArrayArray::UArray_OperatorEqual_ArrayArray()
{
	FunctionData.FunctionName = "operator =";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnsArray = true;
	FunctionData.ReturnType = "element type";
	FunctionData.ParameterData.Add(FParameterData("element type", "lhs", true, false, true));
	FunctionData.ParameterData.Add(FParameterData("element type", "rhs", true, true, true));
}

UValue* UArray_OperatorEqual_ArrayArray::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	UArrayInstance* lhs = Cast<UArrayInstance>(RTS->GetVariable("lhs"));
	UArrayInstance* rhs = Cast<UArrayInstance>(RTS->GetVariable("rhs"));

	lhs->Value = rhs->Value;
	RTS->AddDebugMessage("Storing rhs array into lhs.");
	return lhs;
}




