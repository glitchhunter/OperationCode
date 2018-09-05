// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_FunctionDefinition.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/CodeRunner/CodeRunner.h"
#include "Interpreter/CodeRunner/RuntimeStates/Definitions/RTS_FunctionDefinition.h"


UAST_FunctionDefinition::UAST_FunctionDefinition()
{
	Description = "Function definition";
}


void UAST_FunctionDefinition::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_FunctionDefinition::CreateRuntimeState(UCodeRunner* CodeRunnner)
{
	URTS_FunctionDefinition* RTS_FunctionDefinition = NewObject<URTS_FunctionDefinition>(CodeRunnner);
	RTS_FunctionDefinition->Init(CodeRunnner);
	RTS_FunctionDefinition->SetFunctionDefinition(this);
	return RTS_FunctionDefinition;
}