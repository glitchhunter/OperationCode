// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PuzzleHintData.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPuzzleHintData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	TArray<FString> HintText;


};
