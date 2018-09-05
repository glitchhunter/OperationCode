// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_VariableCall.h"
#include "Interpreter/Parser/AST/Expressions/Calls/AST_VariableCall.h"
#include "Interpreter/SemanticAnalysis/SymbolTable.h"
#include "Interpreter/CodeRunner/Values/TypeValue.h"


void URTS_VariableCall::RunStep()
{ 
	Owner = GetCodeRunner()->ConsumeTempOwner();
	if (!Owner && GetCodeRunner()->GetSymbolTable()->TopOwnedVariableCalls.Contains(VariableCall))
		Owner = GetCodeRunner()->GetSymbolTable()->TopOwner;

	if (Owner)
	{
		UValue* val = Owner->GetVariable(VariableCall->VariableName);
		AddDebugMessage("returning a member variables named " + VariableCall->VariableName + " of type " + val->Type + ".");
		GetCodeRunner()->SetValue(val);
		Finished();
		return;
	}

	UValue* val = GetCodeRunner()->GetVariable(VariableCall->VariableName);
	GetCodeRunner()->SetValue(val);
	AddDebugMessage("Returning a variable named " + VariableCall->VariableName + " of type " + GetCodeRunner()->GetValue()->Type + ".");
	Finished();
}

UAST_Node* URTS_VariableCall::GetNode() const
{
	return VariableCall;
}



