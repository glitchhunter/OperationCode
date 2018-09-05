// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/Expressions/Operators/TwoArguments/Assignment/CompoundAssignment/AST_CompoundAssignment.h"
#include "AST_DivideEqual.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UAST_DivideEqual : public UAST_CompoundAssignment
{
	GENERATED_BODY()
	
public:

	UAST_DivideEqual();
	
	
};
