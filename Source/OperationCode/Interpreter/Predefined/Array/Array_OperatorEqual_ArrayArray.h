// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "Array_OperatorEqual_ArrayArray.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UArray_OperatorEqual_ArrayArray : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UArray_OperatorEqual_ArrayArray();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
	
};
