// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/Expressions/Operators/OneArgument/AST_OneArgument.h"
#include "AST_Not.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UAST_Not : public UAST_OneArgument
{
	GENERATED_BODY()
	
public:

	UAST_Not();
	
	
};
