// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/PredefinedClassInstance.h"
#include "BoolInstance.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UBoolInstance : public UPredefinedClassInstance
{
	GENERATED_BODY()
	
public:

	virtual UBoolInstance* Duplicate_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Value;
	
	
};
