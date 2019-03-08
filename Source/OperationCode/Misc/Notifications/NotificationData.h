// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NotificationType.h"
#include "NotificationData.generated.h"

class UNotificationPayload;

/**
 * 
 */
USTRUCT(BlueprintType)
struct FNotificationData
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString NotificationText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FNotificationTypeData Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UNotificationPayload* Payload;
	
};
