// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "SAP_FlowControlAnalysis.generated.h"


/**
 * Checks that all continues and breaks are inside loops.
 */
UCLASS()
class OPERATIONCODE_API USAP_FlowControlAnalysis : public USemanticAnalysisPhase
{
	GENERATED_BODY()

public:


	virtual void Analyse(UAST_Break* Break) override;

	virtual void Analyse(UAST_Continue* Continue) override;

	virtual void Analyse(UAST_DoWhile* DoWhile) override;

	virtual void Analyse(UAST_For* For) override;

	virtual void Analyse(UAST_While* While) override;



	virtual void Analyse(UAST_Basic* Basic) override { AnalyseChildren(Basic); }

	virtual void Analyse(UAST_Main* Main) override { AnalyseChildren(Main); }

	virtual void Analyse(UAST_ClassDefinition* ClassDefinition) override { AnalyseChildren(ClassDefinition); }

	virtual void Analyse(UAST_FunctionDefinition* FunctionDefinition) override { AnalyseChildren(FunctionDefinition); }

	virtual void Analyse(UAST_If* If) override { AnalyseChildren(If); }

	virtual void Analyse(UAST_FunctionCall* FunctionCall) override { AnalyseChildren(FunctionCall); }

	virtual void Analyse(UAST_Scope* Scope) override { AnalyseChildren(Scope); }



	virtual void Analyse(UAST_VariableCall* VariableCall) override {}

	virtual void Analyse(UAST_BoolLiteral* BoolLiteral) override {}

	virtual void Analyse(UAST_FloatLiteral* FloatLiteral) override {}

	virtual void Analyse(UAST_IntLiteral* IntLiteral) override {}

	virtual void Analyse(UAST_StringLiteral* StringLiteral) override {}

	virtual void Analyse(UAST_Return* Return) override {}

	virtual void Analyse(UAST_Type* Type) override {}

	virtual void Analyse(UAST_VariableDefinition* VariableDefinition) override {}

	virtual void Analyse(UAST_Expression* Expression) override {}

	virtual void Analyse(UAST_TwoArguments* TwoArguments) override {}

	virtual void Analyse(UAST_OneArgument* OneArgument) override {}

	virtual void Analyse(UAST_MemberAccess* MemberAccess) override {}

	virtual void Analyse(UAST_NullptrLiteral* Nullptr) override {}


private:

	
	UPROPERTY()
	TArray<UAST_Loop*> Loops;

};
