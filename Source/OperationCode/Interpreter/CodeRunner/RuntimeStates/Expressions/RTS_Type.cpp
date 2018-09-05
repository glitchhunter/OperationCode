// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_Type.h"
#include "Interpreter/Parser/AST/Expressions/AST_Type.h"
#include "Interpreter/CodeRunner/Values/TypeValue.h"


void URTS_Type::RunStep()
{
	AddDebugMessage("Returning the " + Type->Type + " type.");
	GetCodeRunner()->SetValue(GetCodeRunner()->GetTypeValue(Type->Type));
	Finished();
}

UAST_Node* URTS_Type::GetNode() const
{
	return Type;
}

