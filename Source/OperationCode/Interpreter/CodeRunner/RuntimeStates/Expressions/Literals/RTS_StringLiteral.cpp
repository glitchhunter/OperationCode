// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_StringLiteral.h"
#include "Interpreter/Parser/AST/Expressions/Literals/AST_StringLiteral.h"
#include "Interpreter/CodeRunner/RuntimeStates/Implicit/RTS_InstanceCreator.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/StringInstance.h"



void URTS_StringLiteral::RunStep()
{
	AddDebugMessage("Returning a string of value: " + StringLiteral->Value + ".");
	GetCodeRunner()->SetValue(URTS_InstanceCreator::CreateStringValue(GetCodeRunner(), StringLiteral->Value));
	Finished();
}

UAST_Node* URTS_StringLiteral::GetNode() const
{
	return StringLiteral;
}




