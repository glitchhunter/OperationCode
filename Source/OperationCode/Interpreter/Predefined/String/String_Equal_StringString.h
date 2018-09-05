// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "String_Equal_StringString.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UString_Equal_StringString : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UString_Equal_StringString();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
	
};
