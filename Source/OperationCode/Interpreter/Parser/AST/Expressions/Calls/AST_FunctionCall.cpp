// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_FunctionCall.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Calls/RTS_FunctionCall.h"

UAST_FunctionCall::UAST_FunctionCall()
{
	Description = "Function call";
}

TArray<UAST_Node*> UAST_FunctionCall::GetChildren() const
{
	TArray<UAST_Node*> result = TArray<UAST_Node*>(Arguments);
	return result;
}

void UAST_FunctionCall::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_FunctionCall::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_FunctionCall* RTS_FunctionCall = NewObject<URTS_FunctionCall>(CodeRunner);
	RTS_FunctionCall->Init(CodeRunner);
	RTS_FunctionCall->SetFunctionCall(this);
	return RTS_FunctionCall;
}
