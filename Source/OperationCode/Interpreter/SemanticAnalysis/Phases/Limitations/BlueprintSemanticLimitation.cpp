// Fill out your copyright notice in the Description page of Project Settings.

#include "BlueprintSemanticLimitation.h"

void UBlueprintSemanticLimitation::StartAnalysis(UAST_Node* RootNode)
{
	if (!IsCheckValid(RootNode)) ThrowError(GetErrorMessage());
}

FString UBlueprintSemanticLimitation::GetErrorMessage_Implementation() const
{
	return ErrorMessage;
}


