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
UCLASS(Blueprintable)
class OPERATIONCODE_API UPopUpTextType : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ExposeOnSpawn = "true"))
	TSubclassOf<UPopUpTextWidget> WidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ExposeOnSpawn = "true"))
	float AutoDestroyTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ExposeOnSpawn = "true"))
	USoundBase* Sound;
	
	
};
