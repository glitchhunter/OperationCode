// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "Int_OperatorDivide_IntInt.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UInt_OperatorDivide_IntInt : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UInt_OperatorDivide_IntInt();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
	
};
