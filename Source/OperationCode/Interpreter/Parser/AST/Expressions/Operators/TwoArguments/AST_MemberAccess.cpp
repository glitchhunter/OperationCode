// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_MemberAccess.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Operators/TwoArguments/RTS_MemberAccess.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"

UAST_MemberAccess::UAST_MemberAccess()
{
	Description = ".";
	Sign = ".";
	Precedence = 2;
	Associativity = EOperatorAssociativity::LeftToRight;
}

void UAST_MemberAccess::Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase)
{
	if (SemanticAnalysisPhase) SemanticAnalysisPhase->Analyse(this);
}

URuntimeState* UAST_MemberAccess::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	URTS_MemberAccess* RTS_MemberAccess = NewObject<URTS_MemberAccess>(CodeRunner);
	RTS_MemberAccess->Init(CodeRunner);
	RTS_MemberAccess->SetMemberAccess(this);
	return RTS_MemberAccess;
}

