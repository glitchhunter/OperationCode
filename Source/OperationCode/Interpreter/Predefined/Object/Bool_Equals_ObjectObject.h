// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "Bool_Equals_ObjectObject.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UBool_Equals_ObjectObject : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UBool_Equals_ObjectObject();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
	
};
