// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "Bool_Equals_IntInt.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UBool_Equals_IntInt : public USimplePredefinedFunction
{
	GENERATED_BODY()
	
public:

	UBool_Equals_IntInt();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
};
