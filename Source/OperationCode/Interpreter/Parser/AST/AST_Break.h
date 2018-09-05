// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/AST_Node.h"
#include "AST_Break.generated.h"


/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UAST_Break : public UAST_Node
{
	GENERATED_BODY()
	
public:

	UAST_Break();

	virtual void Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase) override;

	virtual URuntimeState* CreateRuntimeState(UCodeRunner* CodeRunner) override;
	
	
};
