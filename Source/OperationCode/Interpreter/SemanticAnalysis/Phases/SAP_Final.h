// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "SAP_Final.generated.h"

/**
 * Does not iterate through all the nodes, it uses FunctionID data stored by FunctionAnalyisis phase.
 * Iterates through all the functions to see if there is a function that overrides another that is marked as final.
 */
UCLASS()
class OPERATIONCODE_API USAP_Final : public USemanticAnalysisPhase
{
	GENERATED_BODY()
	
public:

	virtual void StartAnalysis(UAST_Node* RootNode) override;

	
	
	
};
