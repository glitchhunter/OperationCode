// Fill out your copyright notice in the Description page of Project Settings.

#include "T_StringLiteral.h"

UT_StringLiteral::UT_StringLiteral()
{
	TokenName = TEXT("String literal");
}

FString UT_StringLiteral::GetTokenName() const
{
	return Super::GetTokenName() + " (" + Value + ")";
}

