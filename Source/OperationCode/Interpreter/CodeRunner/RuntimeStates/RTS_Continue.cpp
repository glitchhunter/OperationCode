// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_Continue.h"
#include "Interpreter/Parser/AST/AST_Continue.h"
#include "Interpreter/Parser/AST/FlowControl/Loops/AST_Loop.h"



void URTS_Continue::RunStep()
{
	while (true)
	{
		URuntimeState* CurrentRTS = GetCodeRunner()->GetRTS();
		if (CurrentRTS->GetNode()->IsA<UAST_Loop>()) break;

		GetCodeRunner()->PopRTS();
	}
	AddDebugMessage("Continuing the loop");
	Finished();
}

UAST_Node* URTS_Continue::GetNode() const
{
	return Continue;
}


