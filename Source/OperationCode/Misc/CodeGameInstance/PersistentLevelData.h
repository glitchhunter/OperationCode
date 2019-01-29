// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "PersistentLevelData.generated.h"

/**
 * 
 */

class UTeachableDataAsset;

UCLASS(Blueprintable)
class OPERATIONCODE_API UPersistentLevelData : public UObject
{
	GENERATED_BODY()
	
public:

	UPersistentLevelData();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CheckpointIndex = -1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSet<UTeachableDataAsset*> ExtraTeachables;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FString> Hints;	
	
};
