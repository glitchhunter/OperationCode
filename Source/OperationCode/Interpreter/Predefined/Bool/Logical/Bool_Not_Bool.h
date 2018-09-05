// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "Bool_Not_Bool.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UBool_Not_Bool : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UBool_Not_Bool();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
	
};
