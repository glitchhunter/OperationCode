// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_BoolLiteral.h"
#include "Interpreter/Parser/AST/Expressions/Literals/AST_BoolLiteral.h"
#include "Interpreter/CodeRunner/RuntimeStates/Implicit/RTS_InstanceCreator.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/BoolInstance.h"



void URTS_BoolLiteral::RunStep()
{
	FString valString = BoolLiteral->Value ? "true" : "false";
	AddDebugMessage("Returning a literal bool with value: " + valString + ".");
	GetCodeRunner()->SetValue(URTS_InstanceCreator::CreateBoolValue(GetCodeRunner(), BoolLiteral->Value));
	Finished();
}

UAST_Node* URTS_BoolLiteral::GetNode() const 
{
	return BoolLiteral;
}



