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
UCLASS(BlueprintType)
class OPERATIONCODE_API UPopUpTextType : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UPopUpTextWidget> WidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float AutoDestroyTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	USoundBase* Sound;
	
	
};
