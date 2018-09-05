// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "Float_Subtract_FloatFloat.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UFloat_Subtract_FloatFloat : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UFloat_Subtract_FloatFloat();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
	
};
