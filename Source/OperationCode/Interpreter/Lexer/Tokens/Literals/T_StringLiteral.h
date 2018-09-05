// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Lexer/Tokens/Literals/T_Literal.h"
#include "T_StringLiteral.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UT_StringLiteral : public UT_Literal
{
	GENERATED_BODY()
	
public:

	UT_StringLiteral();

	UFUNCTION(BlueprintCallable)
	virtual FString GetTokenName() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Value;
	
	
};
