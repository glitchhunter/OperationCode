// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_FunctionCall.h"
#include "Interpreter/Parser/AST/Expressions/Calls/AST_FunctionCall.h"
#include "Interpreter/SemanticAnalysis/SymbolTable.h"
#include "Interpreter/CodeRunner/Values/TypeValue.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/ArrayInstance.h"
#include "Interpreter/Parser/AST/Definition/AST_FunctionDefinition.h"
#include "Interpreter/Parser/AST/Definition/AST_ClassDefinition.h"
#include "Interpreter/CodeRunner/RuntimeStates/Implicit/RTS_ChainedFunctionCall.h"


void URTS_FunctionCall::RunStep()
{
	if (!OwnerSet)
	{
		owner = GetCodeRunner()->ConsumeTempOwner();
		if (!owner && GetCodeRunner()->GetSymbolTable()->TopOwnedFunctionCalls.Contains(FunctionCall))
			owner = GetCodeRunner()->GetSymbolTable()->TopOwner;

		OwnerSet = true;
	}

	// The argument value is stored in CodeRunner
	if (Parameters.Num() < ParamIndex)
	{
		AddDebugMessage("Store returned argument of type " + GetCodeRunner()->GetValue()->Type + " in function call named " + FunctionCall->FunctionName + ".");
		Parameters.Add(GetCodeRunner()->GetValue());
	}

	if (FunctionCall->Arguments.Num() > ParamIndex)
	{
		AddDebugMessage("Run the expression at index " + FString::FromInt(ParamIndex) + " for function call named " + FunctionCall->FunctionName + ".");
		AddRTSToCodeRunner(FunctionCall->Arguments[ParamIndex]);
		ParamIndex++;
		StepCompleted();
		return;
	}

	Definition = GetFunctionDefinition();

	if (!Definition)
	{
		// Special case if there is no default constructor
		AddDebugMessage("Initializing default constructor for instance of type " + FunctionCall->FunctionName + ".");
		URTS_InstanceCreator* instanceCreator = NewObject<URTS_InstanceCreator>(GetCodeRunner());
		instanceCreator->Init(GetCodeRunner());
		instanceCreator->SetValues(FunctionCall->FunctionName, false, TArray<UValue*>());
		GetCodeRunner()->AddRTS(instanceCreator);
		Finished();
		return;

	}

	if(GetCodeRunner()->GetSymbolTable()->ClassNames.Contains(Definition->FunctionData.FunctionName))
	{
		//Special case if this is a constructor
		AddDebugMessage("Initializing constructor for instance of type " + Definition->FunctionData.FunctionName + ".");
		URTS_InstanceCreator* instanceCreator = NewObject<URTS_InstanceCreator>(GetCodeRunner());
		instanceCreator->Init(GetCodeRunner());
		instanceCreator->SetValues(Definition->FunctionData.FunctionName, Definition->FunctionData.ReturnsArray, Parameters);
		GetCodeRunner()->AddRTS(instanceCreator);
		Finished();
		return;
	}


	// Call the function
	AddDebugMessage("Initialize call for function named " + FunctionCall->FunctionName + ".");
	URTS_ChainedFunctionCall* ChainedFunctionCall = NewObject<URTS_ChainedFunctionCall>(GetCodeRunner());
	ChainedFunctionCall->Init(GetCodeRunner());
	ChainedFunctionCall->SetData(Definition, owner, Parameters);
	GetCodeRunner()->AddRTS(ChainedFunctionCall);
	Finished();
}

UAST_FunctionDefinition* URTS_FunctionCall::GetFunctionDefinition()
{
	// Special case for constructors
	if (GetCodeRunner()->GetSymbolTable()->ClassNames.Contains(FunctionCall->FunctionName))
	{
		TArray<FParamSignature> paramSig;
		for (UAST_Expression* exp : FunctionCall->Arguments)
		{
			paramSig.Add(FParamSignature(GetCodeRunner()->GetSymbolTable()->ExpressionReturns[exp].ReturnType, GetCodeRunner()->GetSymbolTable()->ExpressionReturns[exp].ReturnsArray()));
		}

		return GetCodeRunner()->GetSymbolTable()->GetConstructor(FunctionCall->FunctionName, paramSig);
	}

	UAST_ClassDefinition* callerClass = nullptr;
	FString elementType = "";
	if (owner)
	{
		if (owner->IsA<UTypeValue>())
			return GetCodeRunner()->GetSymbolTable()->StaticFunctionCalls[FunctionCall];
		
		UArrayInstance* arrayinstance = Cast<UArrayInstance>(owner);
		if (arrayinstance)
		{
			callerClass = GetCodeRunner()->GetSymbolTable()->ClassNames["array"];
			elementType = arrayinstance->Type;
		}
		else callerClass = GetCodeRunner()->GetSymbolTable()->ClassNames[owner->GetType()];
	}

	return GetCodeRunner()->GetSymbolTable()->GetFunctionDefinitions(FunctionCall, callerClass, elementType, true)[0];
}

UAST_Node* URTS_FunctionCall::GetNode() const
{
	return FunctionCall;
}



