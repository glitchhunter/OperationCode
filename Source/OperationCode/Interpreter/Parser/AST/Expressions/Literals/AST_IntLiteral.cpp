// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_IntLiteral.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Literals/RTS_IntLiteral.h"

UAST_IntLiteral::UAST_IntLiteral()
{
	Description = "Int literal";
}

FString UAST_IntLiteral::GetDescription() const
{
	return Super::GetDescription() + " (" + FString::FromInt(Value) + ")";
}

void UAST_IntLiteral::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_IntLiteral::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_IntLiteral* RTS_IntLiteral = NewObject<URTS_IntLiteral>(CodeRunner);
	RTS_IntLiteral->Init(CodeRunner);
	RTS_IntLiteral->SetIntLiteral(this);
	return RTS_IntLiteral;
}
