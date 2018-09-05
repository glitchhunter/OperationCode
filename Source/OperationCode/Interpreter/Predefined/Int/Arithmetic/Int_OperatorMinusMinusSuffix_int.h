// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "Int_OperatorMinusMinusSuffix_int.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UInt_OperatorMinusMinusSuffix_int : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UInt_OperatorMinusMinusSuffix_int();
	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
	
};
