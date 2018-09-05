// Fill out your copyright notice in the Description page of Project Settings.

#include "Int_Add_Element.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/ArrayInstance.h"



UInt_Add_Element::UInt_Add_Element()
{
	FunctionData.FunctionName = "Add";
	FunctionData.IsConst = false;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = false;
	FunctionData.ReturnType = "int";
	FunctionData.ParameterData.Add(FParameterData("element type", "element", true, true, false));
}

UValue* UInt_Add_Element::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	UValue* val = RTS->GetVariable("element");
	RTS->AddDebugMessage("Adding an element to the array.");
	UArrayInstance* arrayInstance = Cast<UArrayInstance>(RTS->GetOwner());
	arrayInstance->Value.Add(val);
	return URTS_InstanceCreator::CreateIntValue(RTS->GetCodeRunner(), arrayInstance->Value.Num() - 1);
}



