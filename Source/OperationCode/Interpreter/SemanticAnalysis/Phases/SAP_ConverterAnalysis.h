// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "SAP_ConverterAnalysis.generated.h"

/**
 * Checks that all converter functions are valid.
 * Converters must be static.
 * They must have one argument, and it has to be the type 
 * of the class that function belongs to.
 * Converter names must follow a patern: "convert <type>" for explicit
 * and "convert auto <type>" for implicit. Type is the type of class it converts to.
 * Return value must be of the same type as the type defined in name.
 * One class cannot have implicit and explicit converters to another class at the same time.
 * Converter must exist inside a class (cannot ebe defined in global scope).
 * 
 * This function does not iterate through the AST tree. It uses data stored by class and function analysis.
 */
UCLASS()
class OPERATIONCODE_API USAP_ConverterAnalysis : public USemanticAnalysisPhase
{
	GENERATED_BODY()
	
public:

	virtual void StartAnalysis(UAST_Node* Root) override;

private:

	void AnalyseFunction(UAST_FunctionDefinition* Function);

	UPROPERTY()
	UAST_ClassDefinition* CurrentClass;

	TMap<FString, TSet<FString> > StoredConverters;
	
	
};
