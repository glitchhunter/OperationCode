// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "Float_ConvertAuto_Int.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UFloat_ConvertAuto_Int : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UFloat_ConvertAuto_Int();
	
	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
	
};
