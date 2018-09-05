// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_Return.h"
#include "Interpreter/Parser/AST/AST_Return.h"
#include "Interpreter/Parser/AST/Expressions/AST_Expression.h"

class UValue;


void URTS_Return::RunStep()
{
	if (!CheckedReturnExpression && Return->ReturnExpression)
	{
		AddDebugMessage("Solving the return expression.");
		AddRTSToCodeRunner(Return->ReturnExpression);
		CheckedReturnExpression = true;
		StepCompleted();
		return;
	}

	// If there is return expression, get the value from it
	// and place it in the other stack frame
	UValue* returnValue = nullptr;
	if (Return->ReturnExpression) returnValue = GetCodeRunner()->GetValue();

	AddDebugMessage("Finishing function");
	GetCodeRunner()->PopStackFrame();
	GetCodeRunner()->SetValue(returnValue);
	Finished();
}

UAST_Node* URTS_Return::GetNode() const
{
	return Return;
}
