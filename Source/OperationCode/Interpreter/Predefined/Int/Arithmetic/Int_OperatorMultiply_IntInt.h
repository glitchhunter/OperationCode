// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "Int_OperatorMultiply_IntInt.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UInt_OperatorMultiply_IntInt : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UInt_OperatorMultiply_IntInt();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
	
};
