// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/Definition/AST_Definition.h"
#include "AST_ClassDefinition.generated.h"

class UAST_FunctionDefinition;
class UAST_VariableDefinition;

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UAST_ClassDefinition : public UAST_Definition
{
	GENERATED_BODY()
	
public:

	UAST_ClassDefinition();

	virtual TArray<UAST_Node*> GetChildren() const override;

	virtual void Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase) override;

	virtual URuntimeState* CreateRuntimeState(UCodeRunner* CodeRunner) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Instanced)
	TArray<UAST_FunctionDefinition*> FunctionDefinitions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<UAST_VariableDefinition*> VariableDefinitions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString ParentName;
	
	
};
