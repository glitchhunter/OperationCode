// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "Element_Get_Int.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UElement_Get_Int : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UElement_Get_Int();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
	
};
