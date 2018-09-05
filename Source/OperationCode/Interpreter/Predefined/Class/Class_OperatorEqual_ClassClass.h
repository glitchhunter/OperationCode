// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "Class_OperatorEqual_ClassClass.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UClass_OperatorEqual_ClassClass : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UClass_OperatorEqual_ClassClass();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;

private:

	UValue* DuplicateValue(UValue* val);
	
	
	
	
};
