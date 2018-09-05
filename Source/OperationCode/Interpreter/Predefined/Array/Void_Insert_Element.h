// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "Void_Insert_Element.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UVoid_Insert_Element : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UVoid_Insert_Element();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
	
};
