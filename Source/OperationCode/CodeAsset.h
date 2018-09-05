// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "CodeAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class OPERATIONCODE_API UCodeAsset : public UDataAsset
{
	GENERATED_BODY()

public:

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (MultiLine = "true"))
		FString Code;
	
	
};
