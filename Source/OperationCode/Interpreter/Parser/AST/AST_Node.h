// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interpreter/CodeRunner/CodeRunner.h"
#include "AST_Node.generated.h"

class USemanticAnalysisPhase;
class URuntimeState;

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType, Abstract)
class OPERATIONCODE_API UAST_Node : public UObject
{
	GENERATED_BODY()
	
public:

	UAST_Node();

	virtual UWorld* GetWorld() const override;

	UFUNCTION(BlueprintCallable)
	virtual TArray<UAST_Node*> GetChildren() const;

	UFUNCTION(BlueprintPure)
	virtual FString GetDescription() const;

	virtual void Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase) PURE_VIRTUAL(UAST_Node::Analyse, );

	virtual URuntimeState* CreateRuntimeState(UCodeRunner* CodeRunnner) PURE_VIRTUAL(UAST_Node::CreateRuntimeState, { return nullptr; })


protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString Description;

	
	
};
