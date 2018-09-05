// Fill out your copyright notice in the Description page of Project Settings.

#include "T_IntLiteral.h"

UT_IntLiteral::UT_IntLiteral()
{
	TokenName = TEXT("Int literal");
}

FString UT_IntLiteral::GetTokenName() const
{
	return Super::GetTokenName() + " (" + FString::FromInt(Value) + ")";
}
