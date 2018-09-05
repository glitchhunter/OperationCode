// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/AST_Node.h"
#include "AST_Main.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UAST_Main : public UAST_Node
{
	GENERATED_BODY()
	
public:

	UAST_Main();

	TArray<UAST_Node*> GetChildren() const override { return Children; }

	virtual void Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase) override;

	virtual URuntimeState* CreateRuntimeState(UCodeRunner* CodeRunner) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<UAST_Node*> Children;
	
	
};


