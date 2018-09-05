// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/FlowControl/Loops/AST_Loop.h"
#include "AST_For.generated.h"

class UAST_Expression;
class UAST_VariableDefinition;

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UAST_For : public UAST_Loop
{
	GENERATED_BODY()
	
public:

	UAST_For();

	TArray<UAST_Node*> GetChildren() const override;

	virtual void Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase) override;

	virtual URuntimeState* CreateRuntimeState(UCodeRunner* CodeRunner) override;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAST_VariableDefinition* Initialization;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAST_Expression* Condition;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAST_Expression* Update;



	
	
};
