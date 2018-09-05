// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/Expressions/Operators/AST_Operator.h"
#include "AST_OneArgument.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class OPERATIONCODE_API UAST_OneArgument : public UAST_Operator
{
	GENERATED_BODY()
	
public:

	UAST_OneArgument();

	virtual bool HasAllArguments() const;

	virtual void AddArgument(UAST_Expression* Argument);

	virtual TArray<UAST_Node*> GetChildren() const override;

	virtual void Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase) override;

	virtual URuntimeState* CreateRuntimeState(UCodeRunner* CodeRunner) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAST_Expression* Argument;
	
};
