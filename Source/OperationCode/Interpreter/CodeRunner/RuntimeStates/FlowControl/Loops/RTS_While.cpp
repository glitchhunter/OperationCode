// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_While.h"
#include "Interpreter/Parser/AST/FlowControl/Loops/AST_While.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/BoolInstance.h"



void URTS_While::RunStep()
{
	if (!HasAddedScope)
	{
		AddScope();
		HasAddedScope = true;
	}

	if (!CheckedCondition)
	{
		AddDebugMessage("Solving while loop condition.");
		AddRTSToCodeRunner(While->Condition);
		CheckedCondition = true;
		StepCompleted();
		return;
	}

	UBoolInstance* conditionValue = Cast<UBoolInstance>(GetCodeRunner()->GetValue());
	FString DebugString = conditionValue->Value ? TEXT("true") : TEXT("false");
	AddDebugMessage("While loop condition completed. Value is " + DebugString + ".");
	if (conditionValue->Value)
	{
		AddDebugMessage("Running while body.");
		AddRTSToCodeRunner(While->Body);
		CheckedCondition = false;
		StepCompleted();
		return;
	}
	else
	{
		AddDebugMessage("Leaving while loop.");
		Finished();
	}
}

UAST_Node* URTS_While::GetNode() const
{
	return While;
}







