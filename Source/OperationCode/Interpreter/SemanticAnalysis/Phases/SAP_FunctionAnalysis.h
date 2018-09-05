// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/FunctionData.h"
#include "SAP_FunctionAnalysis.generated.h"


/**
 * Check that parameter and return types are defined.
 * Function ID is function signature coupled with the class it belongs to (or global scope if nullptr).
 * Checks to make sure that no duplicate functions exist, as well as checking that return value
 * of overriden functions are same or derivative.
 * Check that there are no arguments with same name.
 * Stores all function IDs and connects them to function definitions.
 * Check that constructors are defined inside a class.
 * Store constructors.
 */
UCLASS()
class OPERATIONCODE_API USAP_FunctionAnalysis : public USemanticAnalysisPhase
{
	GENERATED_BODY()

public:

	virtual void Analyse(UAST_Basic* Basic) override;

	virtual void Analyse(UAST_Main* Main) override;

	virtual void Analyse(UAST_ClassDefinition* ClassDefinition) override;

	virtual void Analyse(UAST_FunctionDefinition* FunctionDefinition) override;



	virtual void Analyse(UAST_VariableDefinition* VariableDefinition) override {}

	virtual void Analyse(UAST_DoWhile* DoWhile) override {}

	virtual void Analyse(UAST_For* For) override {}

	virtual void Analyse(UAST_If* If) override {}

	virtual void Analyse(UAST_While* While) override {}

	virtual void Analyse(UAST_FunctionCall* FunctionCall) override {}

	virtual void Analyse(UAST_VariableCall* VariableCall) override {}

	virtual void Analyse(UAST_BoolLiteral* BoolLiteral) override {}

	virtual void Analyse(UAST_FloatLiteral* FloatLiteral) override {}

	virtual void Analyse(UAST_IntLiteral* IntLiteral) override {}

	virtual void Analyse(UAST_StringLiteral* StringLiteral) override {}

	virtual void Analyse(UAST_TwoArguments* TwoArguments) override {}

	virtual void Analyse(UAST_OneArgument* OneArgument) override {}

	virtual void Analyse(UAST_MemberAccess* MemberAccess) override {}

	virtual void Analyse(UAST_Scope* Scope) override {}

	virtual void Analyse(UAST_Return* Return) override {}

	virtual void Analyse(UAST_Break* Break) override {}

	virtual void Analyse(UAST_Continue* Continue) override {}

	virtual void Analyse(UAST_Type* Type) override {}

	virtual void Analyse(UAST_Expression* Expression) override {}

	virtual void Analyse(UAST_NullptrLiteral* Nullptr) override {}

	
private:

	void CheckTypeValidity(UAST_FunctionDefinition* FunctionDefinition, UAST_ClassDefinition* ownerClass);

	void CheckDuplicateFunctions(UAST_FunctionDefinition* FunctionDefinition, UAST_ClassDefinition* ownerClass);

	void CheckDuplicateArgumentName(UAST_FunctionDefinition* FunctionDefinition, UAST_ClassDefinition* ownerClass);

	void CheckOverrideValidity(UAST_FunctionDefinition* FunctionDefinition, UAST_ClassDefinition* ownerClass);
	

	// Class the function belongs to, nullptr if in global scope
	UPROPERTY()
	UAST_ClassDefinition* owningClass;
	
};
