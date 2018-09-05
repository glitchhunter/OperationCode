// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Lexer/Tokens/Operators/Assignments/AugmentedAssignments/T_AugmentedAssignment.h"
#include "T_ModuloEqual.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UT_ModuloEqual : public UT_AugmentedAssignment
{
	GENERATED_BODY()
	
public:

	UT_ModuloEqual();
	
	
};
