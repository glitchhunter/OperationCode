// Fill out your copyright notice in the Description page of Project Settings.

#include "T_BoolLiteral.h"

UT_BoolLiteral::UT_BoolLiteral()
{
	TokenName = TEXT("Bool literal");
}

FString UT_BoolLiteral::GetTokenName() const
{
	return Super::GetTokenName() + " (" + (Value ? TEXT("True") : TEXT("False")) + ")";
}

