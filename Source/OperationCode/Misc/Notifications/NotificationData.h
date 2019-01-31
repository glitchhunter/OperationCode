// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NotificationData.generated.h"

class UNotificationType;
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
	UNotificationType* Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UNotificationPayload* Payload;
	
};
