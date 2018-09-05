// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "SAP_StoreStatics.generated.h"

UENUM()
enum class ECurrentScope
{
	Global,
	InClass,
	Local
};

/**
 * ** Modifies AST tree! **
 * Stores all static function and variables in symbol table for quick lookup.
 * Marks all global functions and variables as static.
 * Makes sure that localy defined variables are not static.
 */
UCLASS()
class OPERATIONCODE_API USAP_StoreStatics : public USemanticAnalysisPhase
{
	GENERATED_BODY()
	
public:

	virtual void Analyse(UAST_Basic* Basic) override;

	virtual void Analyse(UAST_Main* Main) override;

	virtual void Analyse(UAST_ClassDefinition* ClassDefinition) override;

	virtual void Analyse(UAST_FunctionDefinition* FunctionDefinition) override;

	virtual void Analyse(UAST_VariableDefinition* VariableDefinition) override;



	virtual void Analyse(UAST_DoWhile* DoWhile) override { DefaultBehaviour(DoWhile); }

	virtual void Analyse(UAST_For* For) override { DefaultBehaviour(For); }

	virtual void Analyse(UAST_If* If) override { DefaultBehaviour(If); }

	virtual void Analyse(UAST_While* While) override { DefaultBehaviour(While); }

	virtual void Analyse(UAST_Scope* Scope) override { DefaultBehaviour(Scope); }



	virtual void Analyse(UAST_FunctionCall* FunctionCall) override {}

	virtual void Analyse(UAST_VariableCall* VariableCall) override {}

	virtual void Analyse(UAST_BoolLiteral* BoolLiteral) override {}

	virtual void Analyse(UAST_FloatLiteral* FloatLiteral) override {}

	virtual void Analyse(UAST_IntLiteral* IntLiteral) override {}

	virtual void Analyse(UAST_StringLiteral* StringLiteral) override {}

	virtual void Analyse(UAST_TwoArguments* TwoArguments) override {}

	virtual void Analyse(UAST_OneArgument* OneArgument) override {}

	virtual void Analyse(UAST_MemberAccess* MemberAccess) override {}

	virtual void Analyse(UAST_Return* Return) override {}

	virtual void Analyse(UAST_Break* Break) override {}

	virtual void Analyse(UAST_Continue* Continue) override {}

	virtual void Analyse(UAST_Type* Type) override {}

	virtual void Analyse(UAST_Expression* Expression) override {}

	virtual void Analyse(UAST_NullptrLiteral* Nullptr) override {}



private:

	void DefaultBehaviour(UAST_Node* Node);

	void AddStaticFunction(UAST_FunctionDefinition* FunctionDefinition, FString className);

	void AddStaticVariable(UAST_VariableDefinition* VariableDefinition, FString className);

	
	UPROPERTY()
	UAST_ClassDefinition* CurrentClass;

	UPROPERTY()
	ECurrentScope CurrentScope;
	
	
};
