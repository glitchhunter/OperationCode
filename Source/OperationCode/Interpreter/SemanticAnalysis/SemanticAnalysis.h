// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/InterpreterComponent.h"
#include "SemanticAnalysis.generated.h"

class USymbolTable;
class USemanticAnalysisPhase;

/**
 * 
 */

UCLASS()
class OPERATIONCODE_API USemanticAnalysis : public UInterpreterComponent
{
	GENERATED_BODY()
	
public:

	USemanticAnalysis();

	UFUNCTION(BlueprintCallable)
	USymbolTable* AnalyseAST(UAST_Node* Root, UValue* TopOwner);

	USymbolTable* GetMainSymbolTable() const { return MainSymbolTable; }

	virtual void Clear() override;


protected:

	UPROPERTY()
	TArray<TSubclassOf<USemanticAnalysisPhase> > PhaseClasses;

private:


	UPROPERTY()
	USymbolTable* MainSymbolTable;

	UPROPERTY()
	TArray<USemanticAnalysisPhase*> Phases;
	
};
