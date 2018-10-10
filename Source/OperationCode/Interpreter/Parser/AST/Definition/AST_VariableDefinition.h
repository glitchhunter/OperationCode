// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/Definition/AST_Definition.h"
#include "Interpreter/Parser/AST/Expressions/AST_Expression.h"
#include "AST_VariableDefinition.generated.h"

class UAST_ClassDefinition;

/**
 * 
 */
UCLASS(EditInlineNew)
class OPERATIONCODE_API UAST_VariableDefinition : public UAST_Definition
{
	GENERATED_BODY()
	
public:

	UAST_VariableDefinition();

	virtual TArray<UAST_Node*> GetChildren() const override;

	virtual void Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase) override;

	virtual URuntimeState* CreateRuntimeState(UCodeRunner* CodeRunner) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Instanced)
	UAST_Expression* InitExpression;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsArray;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	bool IsStatic;
	
	
};
