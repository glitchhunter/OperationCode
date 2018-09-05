// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Lexer/Tokens/Specials/T_Special.h"
#include "T_Identifier.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UT_Identifier : public UT_Special
{
	GENERATED_BODY()
	
public:

	UT_Identifier();

	UFUNCTION(BlueprintCallable)
	virtual FString GetTokenName() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ID;
	
	
};
