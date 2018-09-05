// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/Expressions/Operators/TwoArguments/Assignment/AST_Assignment.h"
#include "AST_DirectAssignment.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UAST_DirectAssignment : public UAST_Assignment
{
	GENERATED_BODY()
	
public:

	UAST_DirectAssignment();
	
	
};
