// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_TwoArguments.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Operators/TwoArguments/RTS_TwoArguments.h"

UAST_TwoArguments::UAST_TwoArguments()
{
	NumberOfArguments = 2;
}

bool UAST_TwoArguments::HasAllArguments() const
{
	return IsValid(lhs) && IsValid(rhs);
}

void UAST_TwoArguments::AddArgument(UAST_Expression* Argument)
{
	if (!IsValid(lhs))
	{
		lhs = Argument;
		return;
	}

	if (!IsValid(rhs))
	{
		rhs = Argument;
		return;
	}
}

TArray<UAST_Node*> UAST_TwoArguments::GetChildren() const
{
	TArray<UAST_Node*> result = TArray<UAST_Node*>();
	result.Add(lhs);
	result.Add(rhs);
	return result;
}

void UAST_TwoArguments::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_TwoArguments::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_TwoArguments* RTS_TwoArguments = NewObject<URTS_TwoArguments>(CodeRunner);
	RTS_TwoArguments->Init(CodeRunner);
	RTS_TwoArguments->SetTwoArguments(this);
	return RTS_TwoArguments;
}

