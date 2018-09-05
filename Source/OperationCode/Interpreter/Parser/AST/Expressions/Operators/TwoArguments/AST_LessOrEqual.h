// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/Expressions/Operators/TwoArguments/AST_TwoArguments.h"
#include "AST_LessOrEqual.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UAST_LessOrEqual : public UAST_TwoArguments
{
	GENERATED_BODY()
	
public:

	UAST_LessOrEqual();
	
	
};
