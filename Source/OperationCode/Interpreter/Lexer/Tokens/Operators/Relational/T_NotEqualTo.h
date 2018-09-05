// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Lexer/Tokens/Operators/Relational/T_Relational.h"
#include "T_NotEqualTo.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UT_NotEqualTo : public UT_Relational
{
	GENERATED_BODY()
	
public:

	UT_NotEqualTo();
	
	
};
