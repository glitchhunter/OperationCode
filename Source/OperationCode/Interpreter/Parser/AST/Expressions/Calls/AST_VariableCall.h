// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/Expressions/Calls/AST_Call.h"
#include "AST_VariableCall.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UAST_VariableCall : public UAST_Call
{
	GENERATED_BODY()
	
public:

	UAST_VariableCall();

	virtual void Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase) override;

	virtual URuntimeState* CreateRuntimeState(UCodeRunner* CodeRunner) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadonly)
	FString VariableName;
	
	
	
};
