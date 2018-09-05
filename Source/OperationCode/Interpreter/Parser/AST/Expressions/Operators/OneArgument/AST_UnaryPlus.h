// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/Expressions/Operators/OneArgument/AST_OneArgument.h"
#include "AST_UnaryPlus.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UAST_UnaryPlus : public UAST_OneArgument
{
	GENERATED_BODY()
	
public:

	UAST_UnaryPlus();
	
	
};
