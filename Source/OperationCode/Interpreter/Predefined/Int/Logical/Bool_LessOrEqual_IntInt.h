// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "Bool_LessOrEqual_IntInt.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UBool_LessOrEqual_IntInt : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UBool_LessOrEqual_IntInt();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
	
};
