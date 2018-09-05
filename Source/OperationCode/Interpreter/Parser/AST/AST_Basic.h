// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/AST_Node.h"
#include "AST_Basic.generated.h"

class UAST_Main;
class UAST_ClassDefinition;
class UAST_FunctionDefinition;

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UAST_Basic : public UAST_Node
{
	GENERATED_BODY()
	
public:

	UAST_Basic();

	TArray<UAST_Node*> GetChildren() const override;

	virtual void Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase) override;

	virtual URuntimeState* CreateRuntimeState(UCodeRunner* CodeRunner) override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAST_Main* Main;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	TArray<UAST_ClassDefinition*> PredefinedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	TArray<UAST_FunctionDefinition*> PredefinedFunctions;
	
};
