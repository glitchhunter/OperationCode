// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_NullptrLiteral.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Literals/RTS_NullptrLiteral.h"

UAST_NullptrLiteral::UAST_NullptrLiteral()
{
	Description = "String literal";
}

FString UAST_NullptrLiteral::GetDescription() const
{
	return Super::GetDescription() + " (nullptr)";
}

void UAST_NullptrLiteral::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_NullptrLiteral::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_NullptrLiteral* RTS_NullptrLiteral = NewObject<URTS_NullptrLiteral>(CodeRunner);
	RTS_NullptrLiteral->Init(CodeRunner);
	RTS_NullptrLiteral->SetNullptrLiteral(this);
	return RTS_NullptrLiteral;
}





