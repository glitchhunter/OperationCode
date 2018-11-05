// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TeachableDataAsset.generated.h"

class UUserWidget;

UENUM(BlueprintType)
enum class ETeachableType : uint8
{
	Concept,
	Tutorial
};

USTRUCT(BlueprintType)
struct FTeachableSegment
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Multiline = "true"))
	FString TextSegment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> ExtraWidget;

};


/**
 * 
 */
UCLASS(Blueprintable)
class OPERATIONCODE_API UTeachableDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FTeachableSegment> Segment;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETeachableType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UTeachableDataAsset*> RelatedTeachables;
	
};
