// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_Scope.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/CodeRunner/RuntimeStates/RTS_Scope.h"

UAST_Scope::UAST_Scope()
{
	Description = "Scope";
}

void UAST_Scope::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_Scope::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_Scope* RTS_Scope = NewObject<URTS_Scope>(CodeRunner);
	RTS_Scope->Init(CodeRunner);
	RTS_Scope->SetScope(this);
	return RTS_Scope;
}
