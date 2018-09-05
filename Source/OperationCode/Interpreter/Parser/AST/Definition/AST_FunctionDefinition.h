// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/Definition/AST_Definition.h"
#include "Interpreter/FunctionData.h"
#include "AST_FunctionDefinition.generated.h"

class UAST_Scope;

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UAST_FunctionDefinition : public UAST_Definition
{
	GENERATED_BODY()
	
public:

	UAST_FunctionDefinition();

	virtual void Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase) override;

	virtual URuntimeState* CreateRuntimeState(UCodeRunner* CodeRunner) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FFunctionData FunctionData;

	UPROPERTY()
	UAST_Scope* Scope;
	
	
};
