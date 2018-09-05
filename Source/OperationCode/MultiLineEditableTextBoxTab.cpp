// Fill out your copyright notice in the Description page of Project Settings.

#include "MultiLineEditableTextBoxTab.h"
#include "Widgets/Text/SMultiLineEditableText.h"

void UMultiLineEditableTextBoxTab::InsertAtCurrentLocation(FString string)
{
	MyMultiLineEditableText->InsertTextAtCursor(string);
}


