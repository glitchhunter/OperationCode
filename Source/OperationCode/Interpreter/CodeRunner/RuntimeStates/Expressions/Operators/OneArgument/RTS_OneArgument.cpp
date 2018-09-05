// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_OneArgument.h"
#include "Interpreter/Parser/AST/Expressions/Operators/OneArgument/AST_OneArgument.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Calls/RTS_FunctionCall.h"


void URTS_OneArgument::RunStep()
{
	if (!ArgumentManaged)
	{
		AddDebugMessage("Solving the argument for operator " + OneArgument->GetSign() + ".");
		AddRTSToCodeRunner(OneArgument->Argument);
		ArgumentManaged = true;
		StepCompleted();
		return;
	}

	TArray<UValue*> param;
	param.Add(GetCodeRunner()->GetValue());

	TArray<FParamSignature> paramSig;
	paramSig.Add(FParamSignature(GetCodeRunner()->GetValue()->Type, GetCodeRunner()->GetValue()->IsA<UArrayInstance>()));
	UAST_FunctionDefinition* funDef = GetCodeRunner()->GetSymbolTable()->GetOverloadedOperator(FFunctionSignature("operator " + OneArgument->GetSign(), paramSig));
	AddDebugMessage("Found a suitable function definition for operator " + OneArgument->GetSign() + " with argument of type " + param[0]->Type + ".");
	AddDebugMessage("Suitable function definition is named " + funDef->FunctionData.FunctionName + " and takes one argument of type " + funDef->FunctionData.ParameterData[0].Type + ".");
	URTS_ChainedFunctionCall* chainedFunctionCall = NewObject<URTS_ChainedFunctionCall>(GetCodeRunner());
	chainedFunctionCall->Init(GetCodeRunner());
	chainedFunctionCall->SetData(funDef, nullptr, param);
	GetCodeRunner()->AddRTS(chainedFunctionCall);
	Finished();
}

UAST_Node* URTS_OneArgument::GetNode() const
{
	return OneArgument;
}



