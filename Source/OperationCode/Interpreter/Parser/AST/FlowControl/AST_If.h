// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/FlowControl/AST_FlowControl.h"
#include "AST_If.generated.h"

class UAST_Expression;

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UAST_If : public UAST_FlowControl
{
	GENERATED_BODY()

public:

	UAST_If();

	virtual TArray<UAST_Node*> GetChildren() const override;

	virtual void Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase) override;

	virtual URuntimeState* CreateRuntimeState(UCodeRunner* CodeRunner) override;



	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAST_Expression* Condition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAST_Node* TrueBranch;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAST_Node* FalseBranch;
	
	
};
