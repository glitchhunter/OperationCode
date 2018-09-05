// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_Break.h"
#include "Interpreter/Parser/AST/AST_Break.h"
#include "Interpreter/Parser/AST/FlowControl/Loops/AST_Loop.h"



void URTS_Break::RunStep()
{
	while (true)
	{
		URuntimeState* CurrentRTS = GetCodeRunner()->GetRTS();
		if (CurrentRTS->GetNode()->IsA<UAST_Loop>()) break;

		GetCodeRunner()->PopRTS();
	}
	AddDebugMessage("Breaking out of the loop.");
	GetCodeRunner()->PopRTS();
	Finished();
}

UAST_Node* URTS_Break::GetNode() const
{
	return Break;
}






