// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/AST_Node.h"
#include "AST_Continue.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UAST_Continue : public UAST_Node
{
	GENERATED_BODY()
	
public:

	UAST_Continue();

	virtual void Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase) override;

	virtual URuntimeState* CreateRuntimeState(UCodeRunner* CodeRunner) override;
	
	
};
