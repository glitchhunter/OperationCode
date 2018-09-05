// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "SAP_ReturnAnalysis.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API USAP_ReturnAnalysis : public USemanticAnalysisPhase
{
	GENERATED_BODY()

public:

	virtual void StartAnalysis(UAST_Node* Root) override;

	virtual void Analyse(UAST_Scope* Scope) override;

	virtual void Analyse(UAST_If* If) override;

	virtual void Analyse(UAST_DoWhile* DoWhile) override;

	virtual void Analyse(UAST_While* While) override;

	virtual void Analyse(UAST_For* For) override;

	virtual void Analyse(UAST_Return* Return) override;



	virtual void Analyse(UAST_Basic* Basic) override { AnalyseChildren(Basic); }

	virtual void Analyse(UAST_Main* Main) override { AnalyseChildren(Main); }

	virtual void Analyse(UAST_ClassDefinition* ClassDefinition) override { AnalyseChildren(ClassDefinition); }

	virtual void Analyse(UAST_FunctionDefinition* FunctionDefinition) override { AnalyseChildren(FunctionDefinition); }



	virtual void Analyse(UAST_VariableDefinition* VariableDefinition) override {}

	virtual void Analyse(UAST_FunctionCall* FunctionCall) override {}

	virtual void Analyse(UAST_VariableCall* VariableCall) override {}

	virtual void Analyse(UAST_BoolLiteral* BoolLiteral) override {}

	virtual void Analyse(UAST_FloatLiteral* FloatLiteral) override {}

	virtual void Analyse(UAST_IntLiteral* IntLiteral) override {}

	virtual void Analyse(UAST_StringLiteral* StringLiteral) override {}

	virtual void Analyse(UAST_TwoArguments* TwoArguments) override {}

	virtual void Analyse(UAST_OneArgument* OneArgument) override {}

	virtual void Analyse(UAST_MemberAccess* MemberAccess) override {}

	virtual void Analyse(UAST_Expression* Expression) override {}

	virtual void Analyse(UAST_Break* Break) override {}

	virtual void Analyse(UAST_Continue* Continue) override {}

	virtual void Analyse(UAST_Type* Type) override {}

	virtual void Analyse(UAST_NullptrLiteral* Nullptr) override {}

private:

	bool IsInVoidFunction();

	UPROPERTY()
	UAST_FunctionDefinition* CurrentFunction;

	UPROPERTY()
	bool PathHasReturn;
	
	
	
	
};
