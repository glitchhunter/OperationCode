// Fill out your copyright notice in the Description page of Project Settings.

#include "Bool_Not_Bool.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/BoolInstance.h"


UBool_Not_Bool::UBool_Not_Bool()
{
	FunctionData.FunctionName = "operator !";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "bool";
	FunctionData.ParameterData.Add(FParameterData("bool", "val", true, true, false));
}

UValue* UBool_Not_Bool::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	bool val = RTS->GetBoolValue("val");
	if (val)
	{
		RTS->AddDebugMessage("Val is true, returning false.");
		return URTS_InstanceCreator::CreateBoolValue(RTS->GetCodeRunner(), false);
	}
	RTS->AddDebugMessage("Val is false. Returning true.");
	return URTS_InstanceCreator::CreateBoolValue(RTS->GetCodeRunner(), true);
}





