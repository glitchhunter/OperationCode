// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_StringLiteral.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Literals/RTS_StringLiteral.h"

UAST_StringLiteral::UAST_StringLiteral()
{
	Description = "String literal";
}

FString UAST_StringLiteral::GetDescription() const
{
	return Super::GetDescription() + " (" + Value + ")";
}

void UAST_StringLiteral::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_StringLiteral::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_StringLiteral* RTS_StringLiteral = NewObject<URTS_StringLiteral>(CodeRunner);
	RTS_StringLiteral->Init(CodeRunner);
	RTS_StringLiteral->SetStringLiteral(this);
	return RTS_StringLiteral;
}



