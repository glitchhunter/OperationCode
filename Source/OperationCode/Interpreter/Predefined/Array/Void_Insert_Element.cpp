// Fill out your copyright notice in the Description page of Project Settings.

#include "Void_Insert_Element.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/ArrayInstance.h"



UVoid_Insert_Element::UVoid_Insert_Element()
{
	FunctionData.FunctionName = "Insert";
	FunctionData.IsConst = false;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = false;
	FunctionData.ReturnType = "void";
	FunctionData.ParameterData.Add(FParameterData("element type", "element", true, true, false));
	FunctionData.ParameterData.Add(FParameterData("int", "index", true, true, false));
}

UValue* UVoid_Insert_Element::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	int32 index = RTS->GetIntValue("Index");
	UValue* element = RTS->GetVariable("element");
	UArrayInstance* arrayInstance = Cast<UArrayInstance>(RTS->GetOwner());

	if (index > arrayInstance->Value.Num())
	{
		RTS->AddDebugMessage("index too large. Cannot insert.");
		return nullptr;
	}

	RTS->AddDebugMessage("Adding element of type " + element->Type + " at index " + FString::FromInt(index) + ".");
	arrayInstance->Value.Insert(element, index);
	return nullptr;
}



