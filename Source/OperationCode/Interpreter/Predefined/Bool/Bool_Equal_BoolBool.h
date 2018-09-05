// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "Bool_Equal_BoolBool.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UBool_Equal_BoolBool : public USimplePredefinedFunction
{
	GENERATED_BODY()
	
public:

	UBool_Equal_BoolBool();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
};
