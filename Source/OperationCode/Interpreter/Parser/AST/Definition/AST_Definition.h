// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/AST_Node.h"
#include "AST_Definition.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class OPERATIONCODE_API UAST_Definition : public UAST_Node
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	FString Comment;
	
};
