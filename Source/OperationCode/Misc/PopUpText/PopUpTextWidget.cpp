// Fill out your copyright notice in the Description page of Project Settings.

#include "PopUpTextWidget.h"


void UPopUpTextWidget::Remove_Implementation()
{
	GetWorld()->GetTimerManager().ClearTimer(AutodestroyTimerHandle);
	RemoveFromParent();
}

void UPopUpTextWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetNotificationText(InitialText);
}

void UPopUpTextWidget::StartAutoDestroyTimer(float time)
{
	GetWorld()->GetTimerManager().SetTimer(AutodestroyTimerHandle, this, &UPopUpTextWidget::Remove, time, false);
}