// Fill out your copyright notice in the Description page of Project Settings.

#include "Class_OperatorEqual_ClassClass.h"

UClass_OperatorEqual_ClassClass::UClass_OperatorEqual_ClassClass()
{
	FunctionData.FunctionName = "operator =";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = false;
	FunctionData.IsReturnPassByReference = true;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "class";
	FunctionData.ParameterData.Add(FParameterData("class", "lhs", true, false, false));
	FunctionData.ParameterData.Add(FParameterData("class", "rhs", true, true, false));
}

UValue* UClass_OperatorEqual_ClassClass::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	UValue* lhs = RTS->GetVariable("lhs");
	UValue* rhs = RTS->GetVariable("rhs");
	RTS->AddDebugMessage("Storing the rhs value in lhs variable.");
	UValue* dup = rhs->Duplicate();
	lhs->Variables->Variables = dup->Variables->Variables;
	//lhs->Variables->Variables = rhs->Variables->Variables;
	return lhs;
}

UValue* UClass_OperatorEqual_ClassClass::DuplicateValue(UValue* val)
{
	return nullptr;
}



