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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UNotificationWidget> NotificationWidgetClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPopUpTextType* PopUpTextType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool IsPersistent;
	
};
