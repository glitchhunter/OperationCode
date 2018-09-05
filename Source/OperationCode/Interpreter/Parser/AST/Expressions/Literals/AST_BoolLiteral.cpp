// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_BoolLiteral.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Literals/RTS_BoolLiteral.h"

UAST_BoolLiteral::UAST_BoolLiteral()
{
	Description = "Bool literal";
}

FString UAST_BoolLiteral::GetDescription() const
{
	return Super::GetDescription() + " (" + (Value ? TEXT("True") : TEXT("False")) + ")";
}

void UAST_BoolLiteral::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_BoolLiteral::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_BoolLiteral* RTS_BoolLiteral = NewObject<URTS_BoolLiteral>(CodeRunner);
	RTS_BoolLiteral->Init(CodeRunner);
	RTS_BoolLiteral->SetBoolLiteral(this);
	return RTS_BoolLiteral;
}

