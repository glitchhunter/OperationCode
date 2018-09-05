// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_Break.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/CodeRunner/RuntimeStates/RTS_Break.h"

UAST_Break::UAST_Break()
{
	Description = "break";
}


void UAST_Break::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_Break::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_Break* RTS_Break = NewObject<URTS_Break>(CodeRunner);
	RTS_Break->Init(CodeRunner);
	RTS_Break->SetBreak(this);
	return RTS_Break;
}
