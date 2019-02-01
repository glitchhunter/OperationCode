// Fill out your copyright notice in the Description page of Project Settings.

#include "NotificationWidget.h"

void UNotificationWidget::NativeConstruct()
{
	Super::NativeConstruct();
	SetNotificationText(InitialText);
}


