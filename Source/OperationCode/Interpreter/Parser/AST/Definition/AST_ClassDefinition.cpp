// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_ClassDefinition.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/CodeRunner/RuntimeStates/Definitions/RTS_ClassDefinition.h"


UAST_ClassDefinition::UAST_ClassDefinition()
{
	Description = "ClassDefinition";
}

TArray<UAST_Node*> UAST_ClassDefinition::GetChildren() const
{
	TArray<UAST_Node*> result;

	result.Append(VariableDefinitions);
	result.Append(FunctionDefinitions);

	return result;
}

void UAST_ClassDefinition::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_ClassDefinition::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_ClassDefinition* RTS_ClassDefinition = NewObject<URTS_ClassDefinition>(CodeRunner);
	RTS_ClassDefinition->Init(CodeRunner);
	return RTS_ClassDefinition;
}