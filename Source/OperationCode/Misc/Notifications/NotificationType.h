// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Misc/PopUpText/PopUpTextData.h"
#include "NotificationType.generated.h"

class UNotificationWidget;

/**
 * 
 */

USTRUCT(Blueprintable)
struct OPERATIONCODE_API FNotificationTypeData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UNotificationWidget> NotificationWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FPopUpTextTypeData PopUpTextType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsPersistent = true;

};

UCLASS(Blueprintable)
class OPERATIONCODE_API UNotificationType : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FNotificationTypeData Data;
	
};
