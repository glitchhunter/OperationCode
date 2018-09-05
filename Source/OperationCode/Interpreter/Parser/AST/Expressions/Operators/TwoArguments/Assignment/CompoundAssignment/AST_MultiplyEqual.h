// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/Expressions/Operators/TwoArguments/Assignment/CompoundAssignment/AST_CompoundAssignment.h"
#include "AST_MultiplyEqual.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UAST_MultiplyEqual : public UAST_CompoundAssignment
{
	GENERATED_BODY()
	
public:

	UAST_MultiplyEqual();
	
	
};
