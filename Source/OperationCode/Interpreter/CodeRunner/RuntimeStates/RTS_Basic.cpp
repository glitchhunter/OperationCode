// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_Basic.h"
#include "Interpreter/Parser/AST/AST_Basic.h"
#include "Interpreter/Parser/AST/Definition/AST_ClassDefinition.h"
#include "Interpreter/Parser/AST/Definition/AST_FunctionDefinition.h"



void URTS_Basic::RunStep()
{
	if (CurrentChildIndex == 0) AddScope();
	UAST_Node* currentChild = nullptr;

	while (Basic->GetChildren().IsValidIndex(CurrentChildIndex))
	{
		currentChild = Basic->GetChildren()[CurrentChildIndex];
		CurrentChildIndex++;
		if (currentChild->IsA<UAST_ClassDefinition>() || currentChild->IsA<UAST_FunctionDefinition>())
			continue;

		AddRTSToCodeRunner(currentChild);
		if (Basic->GetChildren().IsValidIndex(CurrentChildIndex)) StepCompleted();
		else Finished();
		return;
	}
	Finished();
}

UAST_Node* URTS_Basic::GetNode() const
{
	return Basic;
}



