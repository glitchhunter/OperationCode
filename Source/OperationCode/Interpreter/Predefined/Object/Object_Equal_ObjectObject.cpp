// Fill out your copyright notice in the Description page of Project Settings.

#include "Object_Equal_ObjectObject.h"


UObject_Equal_ObjectObject::UObject_Equal_ObjectObject()
{
	FunctionData.FunctionName = "operator =";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = false;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "object";
	FunctionData.ParameterData.Add(FParameterData("object", "lhs", true, true, false));
	FunctionData.ParameterData.Add(FParameterData("object", "rhs", true, true, false));
}

UValue* UObject_Equal_ObjectObject::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	UValue* lhs = RTS->GetVariable("lhs");
	UValue* rhs = RTS->GetVariable("rhs");

	RTS->AddDebugMessage("Storing rhs value of type " + rhs->Type + " in the lhs value.");
	lhs->Variables = rhs->Variables;
	return lhs;
}


