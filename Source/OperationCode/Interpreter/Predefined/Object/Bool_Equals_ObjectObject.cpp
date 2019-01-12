// Fill out your copyright notice in the Description page of Project Settings.

#include "Bool_Equals_ObjectObject.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/BoolInstance.h"

UBool_Equals_ObjectObject::UBool_Equals_ObjectObject()
{
	FunctionData.FunctionName = "operator ==";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = false;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "bool";
	FunctionData.ParameterData.Add(FParameterData("object", "lhs", true, true, false));
	FunctionData.ParameterData.Add(FParameterData("object", "rhs", true, true, false));
}

UValue* UBool_Equals_ObjectObject::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	UValue* lhs = RTS->GetVariable("lhs");
	UValue* rhs = RTS->GetVariable("rhs");
	bool result = lhs->Variables == rhs->Variables;

	RTS->AddDebugMessage("Comparing lhs value with rhs value using operator ==.");
	if (result) RTS->AddDebugMessage("Lhs value contains the same instance as the rhs value, returning true.");
	else RTS->AddDebugMessage("Lhs  value does not contain the same instance as rhs value, returning false.");

	return URTS_InstanceCreator::CreateBoolValue(RTS->GetCodeRunner(), result);
}



