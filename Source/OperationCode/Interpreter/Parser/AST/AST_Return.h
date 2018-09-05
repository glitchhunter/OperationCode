// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/AST_Node.h"
#include "AST_Return.generated.h"

class UAST_Expression;

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UAST_Return : public UAST_Node
{
	GENERATED_BODY()

public:

	UAST_Return();

	virtual TArray<UAST_Node*> GetChildren() const override;

	virtual void Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase) override;

	virtual URuntimeState* CreateRuntimeState(UCodeRunner* CodeRunner) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAST_Expression* ReturnExpression;
	
	
};
