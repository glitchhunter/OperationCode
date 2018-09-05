// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "String_Concatenate_StringString.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UString_Concatenate_StringString : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UString_Concatenate_StringString();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
	
};
