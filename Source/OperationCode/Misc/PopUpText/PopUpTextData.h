// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PopUpTextType.h"
#include "PopUpTextData.generated.h"


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
	FPopUpTextTypeData TypeData;
	
};
