// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_VariableDefinition.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/CodeRunner/RuntimeStates/Definitions/RTS_VariableDefinition.h"

UAST_VariableDefinition::UAST_VariableDefinition()
{
	Description = "Variable definition";
}

TArray<UAST_Node*> UAST_VariableDefinition::GetChildren() const
{
	TArray<UAST_Node*> result = TArray<UAST_Node*>();
	if (InitExpression) result.Add(InitExpression);
	return result;
}

void UAST_VariableDefinition::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_VariableDefinition::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_VariableDefinition* RTS_VariableDefinition = NewObject<URTS_VariableDefinition>(CodeRunner);
	RTS_VariableDefinition->Init(CodeRunner);
	RTS_VariableDefinition->SetVariableDefinition(this);
	return RTS_VariableDefinition;
}