// Fill out your copyright notice in the Description page of Project Settings.

#include "InterpreterComponent.h"


void UInterpreterComponent::ThrowError(FString ErrorMessage)
{
	GetInterpreter()->StoreErrorMessage(ErrorMessage);
	ThrewError = true;
}

void UInterpreterComponent::ThrowWarning(FString WarningMessage)
{

}

void UInterpreterComponent::Clear()
{

}


UWorld* UInterpreterComponent::GetWorld() const 
{
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		return GetOuter()->GetWorld();
	}
	else
	{
		return nullptr;
	}
}

