// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/Expressions/Literals/AST_Literal.h"
#include "AST_NullptrLiteral.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UAST_NullptrLiteral : public UAST_Literal
{
	GENERATED_BODY()

public:

	UAST_NullptrLiteral();

	virtual FString GetDescription() const override;

	virtual void Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase) override;

	virtual URuntimeState* CreateRuntimeState(UCodeRunner* CodeRunner) override;


	
	
	
	
};
