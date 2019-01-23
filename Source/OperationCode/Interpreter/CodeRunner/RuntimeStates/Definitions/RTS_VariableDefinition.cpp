// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_VariableDefinition.h"
#include "Interpreter/Parser/AST/Definition/AST_VariableDefinition.h"
#include "Interpreter/SemanticAnalysis/SymbolTable.h"
#include "Interpreter/CodeRunner/Values/Value.h"
#include "Interpreter/CodeRunner/Values/TypeValue.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Calls/RTS_FunctionCall.h"
#include "Interpreter/CodeRunner/RuntimeStates/Implicit/RTS_InstanceCreator.h"
#include "Interpreter/CodeRunner/RuntimeStates/Implicit/RTS_ChainedFunctionCall.h"


void URTS_VariableDefinition::RunStep()
{
	if (!ExpressionManaged)
	{
		if (VariableDefinition->InitExpression)
		{
			AddDebugMessage("Initializing Init expression for definition of variable " + VariableDefinition->Name + ".");
			AddRTSToCodeRunner(VariableDefinition->InitExpression);
			ExpressionManaged = true;
			StepCompleted();
			return;
		}
		else
		{
			AddDebugMessage("Creating default value for definition of variable " + VariableDefinition->Name + ".");
			URTS_InstanceCreator* instanceCreator = NewObject<URTS_InstanceCreator>(GetCodeRunner());
			instanceCreator->Init(GetCodeRunner());
			instanceCreator->SetValues(VariableDefinition->Type, VariableDefinition->IsArray, TArray<UValue*>());
			GetCodeRunner()->AddRTS(instanceCreator);
			ExpressionManaged = true;
			StepCompleted();
			return;
		}
	}

	// Convert the return value to correct type
	if (VariableDefinition->InitExpression && !TypeConverted && !GetCodeRunner()->GetSymbolTable()->IsChildOfByName(GetCodeRunner()->GetValue()->GetType(), VariableDefinition->Type))
	{
		UAST_FunctionDefinition* converter = GetCodeRunner()->GetSymbolTable()->GetImplicitConverterByName(GetCodeRunner()->GetValue()->GetType(), VariableDefinition->Type);
		URTS_ChainedFunctionCall* converterRTS = NewObject<URTS_ChainedFunctionCall>(GetCodeRunner());
		TArray<UValue*> ValueToConvert;
		ValueToConvert.Add(GetCodeRunner()->GetValue());
		converterRTS->Init(GetCodeRunner());
		converterRTS->SetData(converter, GetCodeRunner()->GetTypeValue(VariableDefinition->Type), ValueToConvert);
		GetCodeRunner()->AddRTS(converterRTS);
		TypeConverted = true;
		StepCompleted();
		return;
	}

	AddDebugMessage("Returning the value of newly defined variable " + VariableDefinition->Name + ".");
	GetCodeRunner()->AddVariable(VariableDefinition->Name, GetCodeRunner()->GetValue()->Duplicate());
	Finished();
	return;
}

UAST_Node* URTS_VariableDefinition::GetNode() const
{
	return VariableDefinition;
}




