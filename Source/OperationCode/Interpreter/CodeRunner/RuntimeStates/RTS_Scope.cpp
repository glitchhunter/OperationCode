// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_Scope.h"
#include "Interpreter/Parser/AST/AST_Scope.h"


void URTS_Scope::RunStep()
{
	if (CurrentChildIndex == 0) AddScope();

	if (!Scope->GetChildren().IsValidIndex(CurrentChildIndex))
	{
		Finished();
		return;
	}

	UAST_Node* CurrentChild = Scope->GetChildren()[CurrentChildIndex];
	CurrentChildIndex++;
	AddRTSToCodeRunner(CurrentChild);

	if (Scope->GetChildren().IsValidIndex(CurrentChildIndex)) StepCompleted();
	else Finished();
}

UAST_Node* URTS_Scope::GetNode() const
{
	return Scope;
}

