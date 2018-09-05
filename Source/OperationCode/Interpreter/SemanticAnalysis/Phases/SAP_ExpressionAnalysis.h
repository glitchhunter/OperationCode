// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/SemanticAnalysis/ExpressionReturns.h"
#include "SAP_ExpressionAnalysis.generated.h"


USTRUCT()
struct FExpressionPath
{
	GENERATED_BODY()

public:

	FExpressionPath() {};

	FExpressionPath(UAST_Node* currentStep)
	{
		CurrentStep = currentStep;
	}

	UAST_Node* CurrentStep;

	TSet<UAST_FunctionDefinition*> Functions;

	TMap<FString, FExpressionReturn> Variables;

};


/**
 * Loops through all the nodes and checks if types are compatible.
 * Makes sure that every function and variable called is defined and in scope.
 * Throws error if a non-static variable or function is called from a type instead of value.
 * Stores return types of all expressions in symbol table for debugging.
 * Links function and variable calls to their definitions if they are static.
 */
UCLASS()
class OPERATIONCODE_API USAP_ExpressionAnalysis : public USemanticAnalysisPhase
{
	GENERATED_BODY()
	
public:


	virtual void Analyse(UAST_Basic* Basic) override;

	virtual void Analyse(UAST_Main* Main) override;

	virtual void Analyse(UAST_ClassDefinition* ClassDefinition) override;

	virtual void Analyse(UAST_FunctionDefinition* FunctionDefinition) override;

	virtual void Analyse(UAST_VariableDefinition* VariableDefinition) override;

	virtual void Analyse(UAST_DoWhile* DoWhile) override;

	virtual void Analyse(UAST_For* For) override;

	virtual void Analyse(UAST_If* If) override;

	virtual void Analyse(UAST_While* While) override;

	virtual void Analyse(UAST_FunctionCall* FunctionCall) override;

	virtual void Analyse(UAST_VariableCall* VariableCall) override;

	virtual void Analyse(UAST_BoolLiteral* BoolLiteral) override;

	virtual void Analyse(UAST_FloatLiteral* FloatLiteral) override;

	virtual void Analyse(UAST_IntLiteral* IntLiteral) override;

	virtual void Analyse(UAST_StringLiteral* StringLiteral) override;

	virtual void Analyse(UAST_TwoArguments* TwoArguments) override;

	virtual void Analyse(UAST_OneArgument* OneArgument) override;

	virtual void Analyse(UAST_MemberAccess* MemberAccess) override;

	virtual void Analyse(UAST_Expression* Expression) override;

	virtual void Analyse(UAST_Scope* Scope) override;

	virtual void Analyse(UAST_Return* Return) override;

	virtual void Analyse(UAST_Type* Type) override;

	virtual void Analyse(UAST_NullptrLiteral* Nullptr) override;





	virtual void Analyse(UAST_Break* Break) override {};

	virtual void Analyse(UAST_Continue* Continue) override {};



protected:


	void AddStepToPath(UAST_Node* Step);

	void RemoveLastStep();

	void AddFunctionToLastStep(UAST_FunctionDefinition* FunctionDefinition);

	void AddVariableToLastStep(FString VariableName, FExpressionReturn returnData);

	bool VariableExistsInLastStep(FString VariableName);

	TArray<UAST_FunctionDefinition*> GetFunctionDefinitionsWithExplicitCaller(FString ClassType, FString ReturnType, UAST_FunctionCall* FunctionCall);


	UPROPERTY()
	TArray<FExpressionPath> Path;

	FExpressionReturn Caller = FExpressionReturn("", EReturnMode::Invalid);
	
};
