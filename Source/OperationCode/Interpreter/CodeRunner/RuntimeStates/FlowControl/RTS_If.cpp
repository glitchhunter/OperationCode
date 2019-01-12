// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_If.h"
#include "Interpreter/Parser/AST/FlowControl/AST_If.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/BoolInstance.h"
#include "Interpreter/Parser/AST/Expressions/AST_Expression.h"



void URTS_If::RunStep()
{
	if (!CheckedCondition)
	{
		AddScope();
		AddDebugMessage("Solving if condition.");
		AddRTSToCodeRunner(If->Condition);
		CheckedCondition = true;
		StepCompleted();
		return;
	}

	UBoolInstance* conditionValue = Cast<UBoolInstance>(GetCodeRunner()->GetValue());
	FString DebugString = conditionValue->Value ? TEXT("true") : TEXT("false");
	AddDebugMessage("If condition is " + DebugString + ".");
	if (conditionValue->Value)
	{
		AddRTSToCodeRunner(If->TrueBranch);
		AddDebugMessage("Running true branch.");
	}
	else if (If->FalseBranch)
	{
		AddRTSToCodeRunner(If->FalseBranch);
		AddDebugMessage("Running false branch.");
	}
	else AddDebugMessage("No false branch detected. Finishing the if statement.");

	Finished();
}

UAST_Node* URTS_If::GetNode() const
{
	return If;
}
