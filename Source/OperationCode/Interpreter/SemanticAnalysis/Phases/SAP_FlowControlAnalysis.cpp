// Fill out your copyright notice in the Description page of Project Settings.

#include "SAP_FlowControlAnalysis.h"
#include "Interpreter/SemanticAnalysis/SymbolTable.h"

#include "Interpreter/Parser/AST/AST_Break.h"
#include "Interpreter/Parser/AST/AST_Continue.h"
#include "Interpreter/Parser/AST/AST_Return.h"

#include "Interpreter/Parser/AST/FlowControl/AST_If.h"
#include "Interpreter/Parser/AST/FlowControl/Loops/AST_Loop.h"

#include "Interpreter/Parser/AST/Definition/AST_FunctionDefinition.h"






/*======================
 For
======================*/

void USAP_FlowControlAnalysis::Analyse(UAST_For* For)
{
	Loops.Add(For);
	For->Body->Analyse(this);
	Loops.Pop();
}


/*======================
 While
======================*/

void USAP_FlowControlAnalysis::Analyse(UAST_While* While)
{
	Loops.Add(While);
	While->Body->Analyse(this);
	Loops.Pop();
}


/*======================
 Do while
======================*/

void USAP_FlowControlAnalysis::Analyse(UAST_DoWhile* DoWhile)
{
	Loops.Add(DoWhile);
	DoWhile->Body->Analyse(this);
	Loops.Pop();
}


/*======================
 Break
======================*/

void USAP_FlowControlAnalysis::Analyse(UAST_Break* Break)
{
	// Break should exist within a loop
	if (Loops.Num() <= 0)
	{
		ThrowError("Break keyword found outside a loop.");
		return;
	}

	// Add break to the closest loop
	GetSymbolTable()->Breaks.Add(Break, Loops.Top());
}


/*======================
 Continue
======================*/

void USAP_FlowControlAnalysis::Analyse(UAST_Continue* Continue)
{
	// Continue should exist within a loop
	if (Loops.Num() <= 0)
	{
		ThrowError("Continue keyword found outside a loop.");
		return;
	}

	// Add continue to the closest loop
	GetSymbolTable()->Continues.Add(Continue, Loops.Top());
}





