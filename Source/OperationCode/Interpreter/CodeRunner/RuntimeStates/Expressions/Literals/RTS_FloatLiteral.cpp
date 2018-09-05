// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_FloatLiteral.h"
#include "Interpreter/Parser/AST/Expressions/Literals/AST_FloatLiteral.h"
#include "Interpreter/CodeRunner/RuntimeStates/Implicit/RTS_InstanceCreator.h"



void URTS_FloatLiteral::RunStep()
{
	AddDebugMessage("Returning a float value: " + FString::SanitizeFloat(FloatLiteral->Value) + ".");
	GetCodeRunner()->SetValue(URTS_InstanceCreator::CreateFloatValue(GetCodeRunner(), FloatLiteral->Value));
	Finished();
}

UAST_Node* URTS_FloatLiteral::GetNode() const
{
	return FloatLiteral;
}




