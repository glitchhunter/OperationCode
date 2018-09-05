// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/PredefinedClassInstance.h"
#include "FloatInstance.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UFloatInstance : public UPredefinedClassInstance
{
	GENERATED_BODY()

public:

	virtual UFloatInstance* Duplicate_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value;
	
	
	
	
};
