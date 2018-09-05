// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "SAP_ClassAnalysis.generated.h"

/**
 * Stores all classes in symbol table in order to be able to find them by class name.
 * Stores child-parent relationships in symbol table.
 * Makes sure class names are unique.
 * Makes sure there are no circular dependency between classes.
 */
UCLASS()
class OPERATIONCODE_API USAP_ClassAnalysis : public USemanticAnalysisPhase
{
	GENERATED_BODY()
	
public:

	virtual void StartAnalysis(UAST_Node* RootNode) override;

	virtual void Analyse(UAST_Basic* Basic) override;

	virtual void Analyse(UAST_Main* Main) override;

	virtual void Analyse(UAST_ClassDefinition* ClassDefinition) override;




	virtual void Analyse(UAST_FunctionDefinition* FunctionDefinition) override {}

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

	void StoreChildParentRelationships();

	void CheckForCircularDependency();

};
