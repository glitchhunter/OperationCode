// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_DoWhile.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/CodeRunner/RuntimeStates/FlowControl/Loops/RTS_DoWhile.h"

UAST_DoWhile::UAST_DoWhile()
{
	Description = "Do while";
}

TArray<UAST_Node*> UAST_DoWhile::GetChildren() const
{
	TArray<UAST_Node*> result;

	result.Add(Condition);
	result.Add(Body);

	return result;
}


void UAST_DoWhile::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_DoWhile::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_DoWhile* RTS_DoWhile = NewObject<URTS_DoWhile>(CodeRunner);
	RTS_DoWhile->Init(CodeRunner);
	RTS_DoWhile->SetDoWhile(this);
	return RTS_DoWhile;
}

