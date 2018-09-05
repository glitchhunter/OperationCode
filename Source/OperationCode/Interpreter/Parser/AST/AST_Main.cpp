// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_Main.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/CodeRunner/RuntimeStates/RTS_Main.h"

UAST_Main::UAST_Main()
{
	Description = "Main";
}


void UAST_Main::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_Main::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_Main* RTS_Main = NewObject<URTS_Main>(CodeRunner);
	RTS_Main->Init(CodeRunner);
	RTS_Main->SetMain(this);
	return RTS_Main;
}
