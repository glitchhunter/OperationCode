// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_For.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/Parser/AST/Definition/AST_VariableDefinition.h"
#include "Interpreter/Parser/AST/Expressions/AST_Expression.h"
#include "Interpreter/CodeRunner/RuntimeStates/FlowControl/Loops/RTS_For.h"

UAST_For::UAST_For()
{
	Description = "For";
}

TArray<UAST_Node*> UAST_For::GetChildren() const
{
	TArray<UAST_Node*> result;

	if (Initialization) result.Add(Initialization);
	if (Condition) result.Add(Condition);
	if (Update) result.Add(Update);
	if (Body) result.Add(Body);

	return result;
}


void UAST_For::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_For::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_For* RTS_For = NewObject<URTS_For>(CodeRunner);
	RTS_For->Init(CodeRunner);
	RTS_For->SetFor(this);
	return RTS_For;
}
