// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PopUpTextWidget.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UPopUpTextWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetNotificationText(const FString& Text);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Remove();

	UFUNCTION(BlueprintCallable)
	void StartAutoDestroyTimer(float time);

	void NativeConstruct() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ExposeOnSpawn = "true"))
	FString InitialText;	

	UPROPERTY()
	FTimerHandle AutodestroyTimerHandle;
	
};
