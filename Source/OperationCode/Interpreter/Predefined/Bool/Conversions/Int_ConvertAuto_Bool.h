// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "Int_ConvertAuto_Bool.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UInt_ConvertAuto_Bool : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UInt_ConvertAuto_Bool();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
	
};
