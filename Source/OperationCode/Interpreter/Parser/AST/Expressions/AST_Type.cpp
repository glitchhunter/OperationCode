// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_Type.h"
#include "Interpreter/SemanticAnalysis/SemanticAnalysis.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/RTS_Type.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"


UAST_Type::UAST_Type()
{
	Description = "Type";
}

void UAST_Type::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_Type::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_Type* RTS_Type = NewObject<URTS_Type>(CodeRunner);
	RTS_Type->Init(CodeRunner);
	RTS_Type->SetType(this);
	return RTS_Type;
}


