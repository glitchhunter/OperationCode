// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Variables.generated.h"

class UValue;

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UVariables : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TMap<FString, UValue*> Variables;
	
	
	
};
