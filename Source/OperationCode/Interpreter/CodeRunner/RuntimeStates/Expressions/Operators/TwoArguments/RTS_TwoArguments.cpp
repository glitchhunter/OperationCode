// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_TwoArguments.h"
#include "Interpreter/Parser/AST/Expressions/Operators/TwoArguments/AST_TwoArguments.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Calls/RTS_FunctionCall.h"
#include "Interpreter/FunctionData.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/ArrayInstance.h"
#include "Interpreter/SemanticAnalysis/SymbolTable.h"
#include "Interpreter/CodeRunner/RuntimeStates/Implicit/RTS_ChainedFunctionCall.h"
#include "Interpreter/Parser/AST/Definition/AST_FunctionDefinition.h"


void URTS_TwoArguments::RunStep()
{
	if (ArgumentsManaged == 0)
	{
		AddDebugMessage("Solving the first argument in function call \"operator " + TwoArguments->GetSign() + "\".");
		AddRTSToCodeRunner(TwoArguments->lhs);
		ArgumentsManaged++;
		StepCompleted();
		return;
	}
	
	if (ArgumentsManaged == 1)
	{
		lhsVal = GetCodeRunner()->GetValue();
		AddDebugMessage("Storing the value of the first argument in function call \"operator " + TwoArguments->GetSign() + "\", which is of type " + lhsVal->Type + ".");

		AddDebugMessage("Solving the second argument in function call \"operator " + TwoArguments->GetSign() + "\".");
		AddRTSToCodeRunner(TwoArguments->rhs);
		ArgumentsManaged++;
		StepCompleted();
		return;
	}


	TArray<UValue*> params;
	params.Add(lhsVal);
	params.Add(GetCodeRunner()->GetValue());

	AddDebugMessage("Function call for operator " + TwoArguments->GetSign() + " has arguments of type " + params[0]->Type + " and " + params[1]->Type + ".");

	TArray<FParamSignature> paramSig;
	bool firstArray = params[0]->IsA<UArrayInstance>();
	paramSig.Add(FParamSignature(firstArray ? "element type" : params[0]->Type, firstArray));
	bool secondArray = params[1]->IsA<UArrayInstance>();
	paramSig.Add(FParamSignature(secondArray ? "element type" : params[1]->Type, secondArray));
	UAST_FunctionDefinition* funDef = GetCodeRunner()->GetSymbolTable()->GetOverloadedOperator(FFunctionSignature("operator " + TwoArguments->GetSign(), paramSig));
	URTS_ChainedFunctionCall* chainedFunctionCall = NewObject<URTS_ChainedFunctionCall>(GetCodeRunner());
	chainedFunctionCall->Init(GetCodeRunner());
	chainedFunctionCall->SetData(funDef, nullptr, params);
	GetCodeRunner()->AddRTS(chainedFunctionCall);
	AddDebugMessage("Suitable function definition found for operator " + TwoArguments->GetSign() + ", with arguments of type "
		+ funDef->FunctionData.ParameterData[0].Type + " and " + funDef->FunctionData.ParameterData[1].Type + ".");
	Finished();
}

UAST_Node* URTS_TwoArguments::GetNode() const
{
	return TwoArguments;
}




