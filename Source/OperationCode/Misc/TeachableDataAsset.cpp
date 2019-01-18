// Fill out your copyright notice in the Description page of Project Settings.

#include "TeachableDataAsset.h"
#include "Runtime/UMG/Public/UMG.h"

UUserWidget* UTeachableSegment::CreateTeachableWidget(TSubclassOf<UUserWidget> WidgetClass, UObject* WorldContext)
{
	return CreateWidget<UUserWidget>(WorldContext->GetWorld(), WidgetClass);
}


