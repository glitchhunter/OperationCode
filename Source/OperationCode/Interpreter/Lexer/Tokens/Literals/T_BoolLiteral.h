// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Lexer/Tokens/Literals/T_Literal.h"
#include "T_BoolLiteral.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UT_BoolLiteral : public UT_Literal
{
	GENERATED_BODY()

public:

	UT_BoolLiteral();

	UFUNCTION(BlueprintCallable)
	virtual FString GetTokenName() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Value = false;
	
	
};
