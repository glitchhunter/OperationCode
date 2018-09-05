// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_Continue.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/CodeRunner/RuntimeStates/RTS_Continue.h"

UAST_Continue::UAST_Continue()
{
	Description = "continue";
}


void UAST_Continue::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_Continue::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_Continue* RTS_Continue = NewObject<URTS_Continue>(CodeRunner);
	RTS_Continue->Init(CodeRunner);
	RTS_Continue->SetContinue(this);
	return RTS_Continue;
}
