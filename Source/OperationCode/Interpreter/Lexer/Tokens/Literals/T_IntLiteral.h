// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Lexer/Tokens/Literals/T_Literal.h"
#include "T_IntLiteral.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UT_IntLiteral : public UT_Literal
{
	GENERATED_BODY()
	
public:

	UT_IntLiteral();

	UFUNCTION(BlueprintCallable)
	virtual FString GetTokenName() const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Value = 0;
	
};
