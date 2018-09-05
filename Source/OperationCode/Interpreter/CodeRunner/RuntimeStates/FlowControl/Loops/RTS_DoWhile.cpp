// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_DoWhile.h"
#include "Interpreter/Parser/AST/FlowControl/Loops/AST_DoWhile.h"
#include "Interpreter/Parser/AST/Expressions/AST_Expression.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/BoolInstance.h"



void URTS_DoWhile::RunStep()
{
	if (!HasAddedScope)
	{
		AddScope();
		HasAddedScope = true;
		
		AddDebugMessage("Running do while body for the first time.");
		AddRTSToCodeRunner(DoWhile->Body);
		StepCompleted();
		return;
	}

	if (!CheckedCondition)
	{
		AddDebugMessage("Solving do while condition.");
		AddRTSToCodeRunner(DoWhile->Condition);
		CheckedCondition = true;
		StepCompleted();
		return;
	}

	UBoolInstance* conditionValue = Cast<UBoolInstance>(GetCodeRunner()->GetValue());
	FString DebugString = conditionValue->Value ? TEXT("true") : TEXT("false");
	AddDebugMessage("Solved do while condition. Value is " + DebugString + ".");
	if (conditionValue->Value)
	{
		AddDebugMessage("Running do while body.");
		AddRTSToCodeRunner(DoWhile->Body);
		CheckedCondition = false;
		StepCompleted();
		return;
	}
	else
	{
		AddDebugMessage("Exiting do while loop");
		Finished();
		return;
	}
}

UAST_Node* URTS_DoWhile::GetNode() const
{
	return DoWhile;
}





