// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/Expressions/Calls/AST_Call.h"
#include "AST_FunctionCall.generated.h"


/**
 * 
 */

UCLASS()
class OPERATIONCODE_API UAST_FunctionCall : public UAST_Call
{
	GENERATED_BODY()
	
public:

	UAST_FunctionCall();

	virtual TArray<UAST_Node*> GetChildren() const override;

	virtual void Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase) override;

	virtual URuntimeState* CreateRuntimeState(UCodeRunner* CodeRunner) override;



	UPROPERTY(EditDefaultsOnly, BlueprintReadonly)
	FString FunctionName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadonly)
	TArray<UAST_Expression*> Arguments;

};
