// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/PredefinedClassInstance.h"
#include "ArrayInstance.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UArrayInstance : public UPredefinedClassInstance
{
	GENERATED_BODY()

public:

	virtual UArrayInstance* Duplicate_Implementation() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UValue*> Value;
	
	
	
	
};
