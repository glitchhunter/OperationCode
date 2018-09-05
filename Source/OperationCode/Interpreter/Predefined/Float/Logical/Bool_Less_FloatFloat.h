// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "Bool_Less_FloatFloat.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UBool_Less_FloatFloat : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UBool_Less_FloatFloat();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
	
};
