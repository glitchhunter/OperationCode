// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/Expressions/Operators/TwoArguments/AST_TwoArguments.h"
#include "AST_MemberAccess.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UAST_MemberAccess : public UAST_TwoArguments
{
	GENERATED_BODY()

public:

	UAST_MemberAccess();

	virtual void Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase) override;

	virtual URuntimeState* CreateRuntimeState(UCodeRunner* CodeRunner) override;
	
	
};
