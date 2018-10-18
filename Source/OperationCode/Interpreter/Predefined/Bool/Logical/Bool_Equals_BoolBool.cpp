// Fill out your copyright notice in the Description page of Project Settings.

#include "Bool_Equals_BoolBool.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/BoolInstance.h"


UBool_Equals_BoolBool::UBool_Equals_BoolBool()
{
	FunctionData.FunctionName = "operator ==";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "bool";
	FunctionData.ParameterData.Add(FParameterData("bool", "lhs", true, true, false));
	FunctionData.ParameterData.Add(FParameterData("bool", "rhs", true, true, false));
}

UValue* UBool_Equals_BoolBool::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	bool lhs = RTS->GetBoolValue("lhs");
	bool rhs = RTS->GetBoolValue("rhs");

	FString lhsString = lhs ? "true" : "false";
	FString rhsString = rhs ? "true" : "false";
	FString EqualString = lhs == rhs ? "true" : "false";
	RTS->AddDebugMessage("Lhs is " + lhsString + ", rhs is " + rhsString + ".");
	RTS->AddDebugMessage("Returning " + EqualString + ".");
	return URTS_InstanceCreator::CreateBoolValue(RTS->GetCodeRunner(), lhs == rhs);
}





