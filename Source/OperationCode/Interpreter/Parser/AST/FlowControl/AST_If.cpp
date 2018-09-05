// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_If.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/CodeRunner/RuntimeStates/FlowControl/RTS_If.h"

UAST_If::UAST_If()
{
	Description = "If";
}

TArray<UAST_Node*> UAST_If::GetChildren() const
{
	TArray<UAST_Node*> result;

	if (Condition) result.Add(Condition);
	if (TrueBranch) result.Add(TrueBranch);
	if (FalseBranch) result.Add(FalseBranch);

	return result;
}


void UAST_If::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_If::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_If* RTS_If = NewObject<URTS_If>(CodeRunner);
	RTS_If->Init(CodeRunner);
	RTS_If->SetIf(this);
	return RTS_If;
}
