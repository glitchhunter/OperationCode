// Fill out your copyright notice in the Description page of Project Settings.

#include "Bool_NotEqual_StringString.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/BoolInstance.h"

UBool_NotEqual_StringString::UBool_NotEqual_StringString()
{
	FunctionData.FunctionName = "operator !=";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "bool";
	FunctionData.ParameterData.Add(FParameterData("string", "lhs", true, true, false));
	FunctionData.ParameterData.Add(FParameterData("string", "rhs", true, true, false));
}

UValue* UBool_NotEqual_StringString::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	FString lhs = RTS->GetStringValue("lhs");
	FString rhs = RTS->GetStringValue("rhs");
	bool result = lhs != rhs;

	RTS->AddDebugMessage("Comparing lhs value " + lhs + " with rhs value " + rhs + " using operator !=.");
	if (result) RTS->AddDebugMessage("Lhs value contains a different string from rhs value, returning true.");
	else RTS->AddDebugMessage("Lhs value does not contain a different string from rhs value, returning false.");

	return URTS_InstanceCreator::CreateBoolValue(RTS->GetCodeRunner(), result);
}




