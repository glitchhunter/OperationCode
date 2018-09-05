// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_For.h"
#include "Interpreter/Parser/AST/FlowControl/Loops/AST_For.h"
#include "Interpreter/Parser/AST/Definition/AST_VariableDefinition.h"
#include "Interpreter/Parser/AST/Expressions/AST_Expression.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/BoolInstance.h"



void URTS_For::RunStep()
{
	switch (CurrentState)
	{
	case EForState::Uninitialized:
		AddScope();
		AddDebugMessage("Running initialization from for loop.");
		AddRTSToCodeRunner(For->Initialization);
		CurrentState = EForState::RunningInitialization;
		StepCompleted();
		return;
		break;

	case EForState::RunningInitialization:
		AddDebugMessage("Solving for loop condition.");
		AddRTSToCodeRunner(For->Condition);
		CurrentState = EForState::CheckingCondition;
		StepCompleted();
		return;
		break;

	case EForState::CheckingCondition:
	{
		UBoolInstance* conditionValue = Cast<UBoolInstance>(GetCodeRunner()->GetValue());
		if (!conditionValue)
		{
			UE_LOG(LogTemp, Fatal, TEXT("Expected a bool in for condition."));
			return;
		}
		FString DebugString = conditionValue->Value ? TEXT("true") : TEXT("false");
		AddDebugMessage("For loop condition solved. Value is " + DebugString + ".");
		if (!conditionValue->Value)
		{
			AddDebugMessage("Exiting for loop.");
			Finished();
			return;
		}

		AddDebugMessage("Running for loop body.");
		AddRTSToCodeRunner(For->Body);
		CurrentState = EForState::RunningLoopBody;
		StepCompleted();
		return;
		break;
	}
	case EForState::RunningLoopBody:
		AddDebugMessage("For loop body completed. Running update.");
		AddRTSToCodeRunner(For->Update);
		CurrentState = EForState::RunningUpdate;
		StepCompleted();
		return;
		break;

	case EForState::RunningUpdate:
		AddDebugMessage("Solving for loop condition.");
		AddRTSToCodeRunner(For->Condition);
		CurrentState = EForState::CheckingCondition;
		StepCompleted();
		return;
		break;

	default:
		break;
	}
}

UAST_Node* URTS_For::GetNode() const
{
	return For;
}

