// Fill out your copyright notice in the Description page of Project Settings.

#include "T_FloatLiteral.h"

UT_FloatLiteral::UT_FloatLiteral()
{
	TokenName = TEXT("Float literal");
}

FString UT_FloatLiteral::GetTokenName() const
{
	return Super::GetTokenName() + " (" + FString::SanitizeFloat(Value) + ")";
}


