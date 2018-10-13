// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "UnaryMinus_Float.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UUnaryMinus_Float : public USimplePredefinedFunction
{
	GENERATED_BODY()
	

public:

	UUnaryMinus_Float();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;



	
	
};
