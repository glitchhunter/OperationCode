// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelFlowAsset.generated.h"

class ULevelDataAsset;

USTRUCT(BlueprintType)
struct FChapterData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ChapterName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<ULevelDataAsset*> Levels;
};

/**
 * 
 */
UCLASS(BlueprintType)
class OPERATIONCODE_API ULevelFlowAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FChapterData> Chapters;
	
};
