// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "SAP_OperatorAnalysis.generated.h"

struct FFunctionID;

/**
 * Checks if overloaded operators are overloaded correctly.
 * Since all functions were alredy parsed by FunctionAnalysis, 
 * this phase does not iterate through the AST.
 * Operators are overloaded in C# style.
 * Functions must be static.
 * They must match certain function signature.
 * Functions must be declared inside a class that is used as an argument type.
 * Some overloads must always return bool (<, >=, !=...).
 * Also makes sure there are no duplicate overloads. 
 * Example: a + b can be overloaded in class of type a or b, but not in both. 
 */
UCLASS()
class OPERATIONCODE_API USAP_OperatorAnalysis : public USemanticAnalysisPhase
{
	GENERATED_BODY()
	
public:

	USAP_OperatorAnalysis();
	
	virtual void StartAnalysis(UAST_Node* RootNode) override;

private:

	bool IsInProperClass(FFunctionID FunctionID);

	// Keys are operators, if value is true, operator must return a bool.
	UPROPERTY()
	TMap<FString, bool> BinaryOperatorReturns;

	UPROPERTY()
	TMap<FString, bool> UnaryOperatorReturns;

	
};
