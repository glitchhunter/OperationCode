// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "Object_Equal_ObjectObject.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UObject_Equal_ObjectObject : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UObject_Equal_ObjectObject();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
};
