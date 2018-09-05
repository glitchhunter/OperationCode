// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_IntLiteral.h"
#include "Interpreter/Parser/AST/Expressions/Literals/AST_IntLiteral.h"
#include "Interpreter/CodeRunner/RuntimeStates/Implicit/RTS_InstanceCreator.h"



void URTS_IntLiteral::RunStep()
{
	AddDebugMessage("Returning an int value : " + FString::FromInt(IntLiteral->Value) + ".");
	GetCodeRunner()->SetValue(URTS_InstanceCreator::CreateIntValue(GetCodeRunner(), IntLiteral->Value));
	Finished();
}

UAST_Node* URTS_IntLiteral::GetNode() const
{
	return IntLiteral;
}


