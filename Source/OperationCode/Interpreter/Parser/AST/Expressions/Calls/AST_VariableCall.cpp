// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_VariableCall.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Calls/RTS_VariableCall.h"

UAST_VariableCall::UAST_VariableCall()
{
	Description = "Variable call";
}

void UAST_VariableCall::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_VariableCall::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_VariableCall* RTS_VariableCall = NewObject<URTS_VariableCall>(CodeRunner);
	RTS_VariableCall->Init(CodeRunner);
	RTS_VariableCall->SetVariableCall(this);
	return RTS_VariableCall;
}
