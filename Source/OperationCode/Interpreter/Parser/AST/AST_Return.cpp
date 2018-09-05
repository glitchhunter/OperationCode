// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_Return.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/CodeRunner/RuntimeStates/RTS_Return.h"
#include "Interpreter/Parser/AST/Expressions/AST_Expression.h"

UAST_Return::UAST_Return()
{
	Description = "Return";
}

TArray<UAST_Node*> UAST_Return::GetChildren() const
{
	TArray<UAST_Node*> Result;
	if (ReturnExpression) Result.Add(ReturnExpression);
	return Result;
}


void UAST_Return::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_Return::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_Return* RTS_Return = NewObject<URTS_Return>(CodeRunner);
	RTS_Return->Init(CodeRunner);
	RTS_Return->SetReturn(this);
	return RTS_Return;
}