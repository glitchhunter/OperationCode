// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/PredefinedFunction.h"
#include "Interpreter/Predefined/SimpleFunctionDefinitionRTS.h"
#include "SimplePredefinedFunction.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API USimplePredefinedFunction : public UPredefinedFunction
{
	GENERATED_BODY()

public:


	virtual URuntimeState* CreateRuntimeState(UCodeRunner* CodeRunner) override;

	UFUNCTION(BlueprintNativeEvent)
	UValue* Run(USimpleFunctionDefinitionRTS* RTS);


};
