// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "Bool_ConvertAuto_Int.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UBool_ConvertAuto_Int : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UBool_ConvertAuto_Int();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
	
};
