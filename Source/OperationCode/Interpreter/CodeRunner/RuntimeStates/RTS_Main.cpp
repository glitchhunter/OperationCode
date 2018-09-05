// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_Main.h"
#include "Interpreter/Parser/AST/AST_Main.h"
#include "Interpreter/Parser/AST/Definition/AST_ClassDefinition.h"
#include "Interpreter/Parser/AST/Definition/AST_FunctionDefinition.h"



void URTS_Main::RunStep()
{
	if (CurrentChildIndex == 0) AddScope();
	UAST_Node* currentChild = nullptr;

	while (Main->GetChildren().IsValidIndex(CurrentChildIndex))
	{
		currentChild = Main->GetChildren()[CurrentChildIndex];
		CurrentChildIndex++;
		if (currentChild->IsA<UAST_ClassDefinition>() || currentChild->IsA<UAST_FunctionDefinition>())
			continue;

		AddRTSToCodeRunner(currentChild);
		if (Main->GetChildren().IsValidIndex(CurrentChildIndex)) StepCompleted();
		else Finished();
		return;
	}
	Finished();
}

UAST_Node* URTS_Main::GetNode() const
{
	return Main;
}


