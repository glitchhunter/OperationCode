// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/PredefinedClassInstance.h"
#include "IntInstance.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UIntInstance : public UPredefinedClassInstance
{
	GENERATED_BODY()

public:

	virtual UIntInstance* Duplicate_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Value;
	
	
	
	
};
