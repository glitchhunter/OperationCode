// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/MultiLineEditableText.h"
#include "MultiLineEditableTextBoxTab.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UMultiLineEditableTextBoxTab : public UMultiLineEditableText
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	void InsertAtCurrentLocation(FString string);
	
	
};
