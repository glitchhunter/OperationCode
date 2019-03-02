// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "NotificationType.generated.h"

class UNotificationWidget;
class UPopUpTextType;

/**
 * 
 */
UCLASS(BlueprintType)
class OPERATIONCODE_API UNotificationType : public UDataAsset
{
	GENERATED_BODY()
	
public:

	UNotificationType();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ExposeOnSpawn = "true"))
	TSubclassOf<UNotificationWidget> NotificationWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ExposeOnSpawn = "true"))
	UPopUpTextType* PopUpTextType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Meta = (ExposeOnSpawn = "true"))
	bool IsPersistent;
	
};
