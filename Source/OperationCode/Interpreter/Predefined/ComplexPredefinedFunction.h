// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/PredefinedFunction.h"
#include "ComplexPredefinedFunction.generated.h"

class UComplexFunctionDefinitionRTS;

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UComplexPredefinedFunction : public UPredefinedFunction
{
	GENERATED_BODY()
	
public:

	virtual URuntimeState* CreateRuntimeState(UCodeRunner* CodeRunner) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		TSubclassOf<UComplexFunctionDefinitionRTS> RTSClass;
	
	
};
