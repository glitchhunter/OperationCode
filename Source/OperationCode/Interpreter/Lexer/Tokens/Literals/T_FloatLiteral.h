// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Lexer/Tokens/Literals/T_Literal.h"
#include "T_FloatLiteral.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UT_FloatLiteral : public UT_Literal
{
	GENERATED_BODY()

public:

	UT_FloatLiteral();

	UFUNCTION(BlueprintCallable)
	virtual FString GetTokenName()  const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value = 0.0f;
	
	
};
