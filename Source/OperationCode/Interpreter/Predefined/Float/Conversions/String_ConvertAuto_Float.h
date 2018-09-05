// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "String_ConvertAuto_Float.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UString_ConvertAuto_Float : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UString_ConvertAuto_Float();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
	
};
