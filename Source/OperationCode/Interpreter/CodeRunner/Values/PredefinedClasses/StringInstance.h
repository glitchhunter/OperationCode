// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/PredefinedClassInstance.h"
#include "StringInstance.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UStringInstance : public UPredefinedClassInstance
{
	GENERATED_BODY()

public:

	virtual UStringInstance* Duplicate_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Value;
	
	
	
	
};
