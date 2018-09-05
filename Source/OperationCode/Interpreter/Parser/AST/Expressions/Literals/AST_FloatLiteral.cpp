// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_FloatLiteral.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Literals/RTS_FloatLiteral.h"

UAST_FloatLiteral::UAST_FloatLiteral()
{
	Description = "Float literal";
}

FString UAST_FloatLiteral::GetDescription() const
{
	return Super::GetDescription() + " (" + FString::SanitizeFloat(Value) + ")";
}

void UAST_FloatLiteral::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_FloatLiteral::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_FloatLiteral* RTS_FloatLiteral = NewObject<URTS_FloatLiteral>(CodeRunner);
	RTS_FloatLiteral->Init(CodeRunner);
	RTS_FloatLiteral->SetFloatLiteral(this);
	return RTS_FloatLiteral;
}



