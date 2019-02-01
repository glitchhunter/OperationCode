// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PopUpTextData.generated.h"


class UPopUpTextType;
/**
 * 
 */
USTRUCT(BlueprintType)
struct FPopUpTextData
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString PopUpText;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPopUpTextType* Type;
	
};
