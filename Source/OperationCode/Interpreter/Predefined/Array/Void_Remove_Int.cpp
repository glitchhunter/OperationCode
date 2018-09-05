// Fill out your copyright notice in the Description page of Project Settings.

#include "Void_Remove_Int.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/ArrayInstance.h"



UVoid_Remove_Int::UVoid_Remove_Int()
{
	FunctionData.FunctionName = "Remove";
	FunctionData.IsConst = false;
	FunctionData.IsFinal = true;
	FunctionData.IsReturnPassByReference = false;
	FunctionData.IsStatic = false;
	FunctionData.ReturnType = "void";
	FunctionData.ParameterData.Add(FParameterData("int", "elementIndex", true, true, false));
}

UValue* UVoid_Remove_Int::Run_Implementation(USimpleFunctionDefinitionRTS* RTS)
{
	int32 index = RTS->GetIntValue("elementIndex");
	UArrayInstance* arrayInstance = Cast<UArrayInstance>(RTS->GetOwner());
	if (index >= arrayInstance->Value.Num())
	{
		RTS->AddDebugMessage("Index to large. Cannot remove element at index " + FString::FromInt(index) + ".");
		return nullptr;
	}
	RTS->AddDebugMessage("Removing element at index " + FString::FromInt(index) + ".");
	arrayInstance->Value.RemoveAt(index);
	return nullptr;
}





