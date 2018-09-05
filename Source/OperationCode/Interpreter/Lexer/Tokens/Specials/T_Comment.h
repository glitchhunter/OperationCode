// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Lexer/Tokens/Specials/T_Special.h"
#include "T_Comment.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UT_Comment : public UT_Special
{
	GENERATED_BODY()
	
public:

	UT_Comment();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Comment;
	
	
};
