// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_OneArgument.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Operators/OneArgument/RTS_OneArgument.h"

UAST_OneArgument::UAST_OneArgument()
{
	NumberOfArguments = 1;
}

bool UAST_OneArgument::HasAllArguments() const
{
	return IsValid(Argument);
}

void UAST_OneArgument::AddArgument(UAST_Expression* NewArgument)
{
	Argument = NewArgument;
}

TArray<UAST_Node*> UAST_OneArgument::GetChildren() const
{
	TArray<UAST_Node*> result = TArray<UAST_Node*>();
	result.Add(Argument);
	return result;
}


void UAST_OneArgument::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_OneArgument::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_OneArgument* RTS_OneArgument = NewObject<URTS_OneArgument>(CodeRunner);
	RTS_OneArgument->Init(CodeRunner);
	RTS_OneArgument->SetOneArgument(this);
	return RTS_OneArgument;
}

