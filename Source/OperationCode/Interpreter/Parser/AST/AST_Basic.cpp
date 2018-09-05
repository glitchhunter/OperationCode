// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_Basic.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/Parser/AST/AST_Main.h"
#include "Interpreter/CodeRunner/RuntimeStates/RTS_Basic.h"


UAST_Basic::UAST_Basic()
{
	Description = "Basic";
}

TArray<UAST_Node*> UAST_Basic::GetChildren() const
{
	TArray<UAST_Node*> children;
	children.Append(PredefinedClasses);
	children.Append(PredefinedFunctions);
	if (Main) children.Add(Main);
	return children;
}

void UAST_Basic::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_Basic::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_Basic* RTS_Basic = NewObject<URTS_Basic>(CodeRunner);
	RTS_Basic->Init(CodeRunner);
	RTS_Basic->SetBasic(this);
	return RTS_Basic;
}

