// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NotificationWidget.generated.h"

class UNotificationPayload;

/**
 * 
 */
UCLASS(Abstract)
class OPERATIONCODE_API UNotificationWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetNotificationText(const FString& Text);

	void NativeConstruct() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn = "true"))
	FString InitialText;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn = "true"))
	UNotificationPayload* Payload;
	
	
};
