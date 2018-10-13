// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "UnaryPlus_Float.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UUnaryPlus_Float : public USimplePredefinedFunction
{
	GENERATED_BODY()


public:

	UUnaryPlus_Float();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;




	
	
	
	
};
