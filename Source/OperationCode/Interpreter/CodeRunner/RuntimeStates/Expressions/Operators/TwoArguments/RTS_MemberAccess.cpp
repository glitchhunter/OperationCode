// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_MemberAccess.h"
#include "Interpreter/Parser/AST/Expressions/Operators/TwoArguments/AST_MemberAccess.h"


void URTS_MemberAccess ::RunStep()
{

	if (!CalleeHandeled)
	{
		// Solving lhs (caller)
		AddDebugMessage("Solving the caller in member access.");
		AddRTSToCodeRunner(MemberAccess->lhs);
		CalleeHandeled = true;
		StepCompleted();
		return;
	}

	// Store lhs value as owner of calling function or variable
	lhsVal = GetCodeRunner()->GetValue();
	AddDebugMessage("Storing caller, which is of type " + lhsVal->Type + ", and solving callee.");
	GetCodeRunner()->SetTempOwner(lhsVal);
	AddRTSToCodeRunner(MemberAccess->rhs);
	Finished();
}

UAST_Node* URTS_MemberAccess::GetNode() const
{
	return MemberAccess;
}




