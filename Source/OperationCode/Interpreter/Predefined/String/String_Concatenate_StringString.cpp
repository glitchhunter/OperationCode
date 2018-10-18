// Fill out your copyright notice in the Description page of Project Settings.

#include "String_Concatenate_StringString.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/StringInstance.h"

UString_Concatenate_StringString::UString_Concatenate_StringString()
{
	FunctionData.FunctionName = "operator +";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = true;
	FunctionData.ReturnType = "string";
	FunctionData.ParameterData.Add(FParameterData("string", "lhs", true, true, false));
	FunctionData.ParameterData.Add(FParameterData("string", "rhs", true, true, false));
}

UValue* UString_Concatenate_StringString::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	FString lhs = RTS->GetStringValue("lhs");
	FString rhs = RTS->GetStringValue("rhs");
	FString result = lhs + rhs;

	RTS->AddDebugMessage("Concatenating lhs string " + lhs + " and rhs " + rhs + ".");
	RTS->AddDebugMessage("Returning " + result + ".");
	return URTS_InstanceCreator::CreateStringValue(RTS->GetCodeRunner(), result);
}



