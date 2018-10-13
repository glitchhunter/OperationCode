// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "UnaryPlus_Int.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UUnaryPlus_Int : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UUnaryPlus_Int();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
	
};
