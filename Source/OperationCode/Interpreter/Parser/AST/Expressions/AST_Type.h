// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/Expressions/AST_Expression.h"
#include "AST_Type.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UAST_Type : public UAST_Expression
{
	GENERATED_BODY()
	
public:

	UAST_Type();

	virtual void Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase);

	virtual URuntimeState* CreateRuntimeState(UCodeRunner* CodeRunner) override;
	
	UPROPERTY()
		FString Type;
};
