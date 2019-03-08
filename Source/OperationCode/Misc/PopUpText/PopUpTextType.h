// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PopUpTextType.generated.h"

class UPopUpTextWidget;
class USoundBase;

/**
 * 
 */

USTRUCT(Blueprintable)
struct OPERATIONCODE_API FPopUpTextTypeData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UPopUpTextWidget> WidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AutoDestroyTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundBase* Sound;
};

UCLASS(Blueprintable)
class OPERATIONCODE_API UPopUpTextType : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FPopUpTextTypeData Data;
	
};
