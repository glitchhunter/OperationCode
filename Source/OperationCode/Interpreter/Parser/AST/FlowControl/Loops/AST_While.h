// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/FlowControl/Loops/AST_Loop.h"
#include "AST_While.generated.h"

class UAST_Expression;

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UAST_While : public UAST_Loop
{
	GENERATED_BODY()

public:

	UAST_While();

	TArray<UAST_Node*> GetChildren() const override;

	virtual void Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase) override;

	virtual URuntimeState* CreateRuntimeState(UCodeRunner* CodeRunner) override;



	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAST_Expression* Condition;


	
	
};
