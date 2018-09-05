// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "Bool_NotEqual_BoolBool.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UBool_NotEqual_BoolBool : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UBool_NotEqual_BoolBool();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
	
};
