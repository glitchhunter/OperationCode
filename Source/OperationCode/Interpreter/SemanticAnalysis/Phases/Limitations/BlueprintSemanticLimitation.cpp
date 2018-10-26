// Fill out your copyright notice in the Description page of Project Settings.

#include "BlueprintSemanticLimitation.h"

void UBlueprintSemanticLimitation::StartAnalysis(UAST_Node* RootNode)
{
	FString Message;
	if (!IsCheckValid(RootNode, Message)) ThrowError(Message);
}


