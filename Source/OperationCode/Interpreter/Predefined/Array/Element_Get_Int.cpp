// Fill out your copyright notice in the Description page of Project Settings.

#include "Element_Get_Int.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/ArrayInstance.h"



UElement_Get_Int::UElement_Get_Int()
{
	FunctionData.FunctionName = "Get";
	FunctionData.IsConst = true;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = true;
	FunctionData.IsStatic = false;
	FunctionData.ReturnType = "element type";
	FunctionData.ParameterData.Add(FParameterData("int", "index", true, true, false));
}

UValue* UElement_Get_Int::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	int32 index = RTS->GetIntValue("index");
	UArrayInstance* arrayInstance = Cast<UArrayInstance>(RTS->GetOwner());

	// Throw runtime error if we try to get an element at an invalid index
	if (!arrayInstance->Value.IsValidIndex(index))
	{
		RTS->ThrowRuntimeError("Tried to access an element at index " + FString::FromInt(index)
			+ " in array of size " + FString::FromInt(arrayInstance->Value.Num()) + ".");
		return nullptr;
	}
	RTS->AddDebugMessage("Returning the element at index " + FString::FromInt(index) + ".");
	return arrayInstance->Value[index];
}





