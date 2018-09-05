// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_NullptrLiteral.h"
#include "Interpreter/Parser/AST/Expressions/Literals/AST_NullptrLiteral.h"
#include "Interpreter/CodeRunner/RuntimeStates/Implicit/RTS_InstanceCreator.h"



void URTS_NullptrLiteral::RunStep()
{
	AddDebugMessage("Returning a nullptr.");
	GetCodeRunner()->SetValue(URTS_InstanceCreator::CreateNullValue(GetCodeRunner(), "object"));
	Finished();
}

UAST_Node* URTS_NullptrLiteral::GetNode() const
{
	return Nullptr;
}




