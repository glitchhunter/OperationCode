// Fill out your copyright notice in the Description page of Project Settings.

#include "T_Identifier.h"

UT_Identifier::UT_Identifier()
{
	TokenName = TEXT("Identifier");
}

FString UT_Identifier::GetTokenName() const
{
	return Super::GetTokenName() + " (" + ID + ")";
}


