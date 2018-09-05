// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_While.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/CodeRunner/RuntimeStates/FlowControl/Loops/RTS_While.h"

UAST_While::UAST_While()
{
	Description = "While";
}

TArray<UAST_Node*> UAST_While::GetChildren() const
{
	TArray<UAST_Node*> result;

	result.Add(Condition);
	result.Add(Body);

	return result;
}


void UAST_While::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_While::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_While* RTS_While = NewObject<URTS_While>(CodeRunner);
	RTS_While->Init(CodeRunner);
	RTS_While->SetWhile(this);
	return RTS_While;
}
