// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "Int_OperatorPlusPlusPrefix_Int.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UInt_OperatorPlusPlusPrefix_Int : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UInt_OperatorPlusPlusPrefix_Int();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
	
};
