// Fill out your copyright notice in the Description page of Project Settings.

#include "Int_Size.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/ArrayInstance.h"



UInt_Size::UInt_Size()
{
	FunctionData.FunctionName = "Size";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = false;
	FunctionData.ReturnType = "int";
}

UValue* UInt_Size::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	RTS->AddDebugMessage("Returning the size of the array.");
	UArrayInstance* arrayInstance = Cast<UArrayInstance>(RTS->GetOwner());
	return URTS_InstanceCreator::CreateIntValue(RTS->GetCodeRunner(), arrayInstance->Value.Num());
}




