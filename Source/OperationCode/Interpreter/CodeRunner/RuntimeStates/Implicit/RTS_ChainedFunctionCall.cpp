// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_ChainedFunctionCall.h"
#include "Interpreter/Parser/AST/Definition/AST_FunctionDefinition.h"
#include "Interpreter/SemanticAnalysis/SymbolTable.h"

void URTS_ChainedFunctionCall::SetCodeRunner(UCodeRunner* CodeRun)
{
	Init(CodeRun);
}

void URTS_ChainedFunctionCall::RunStep()
{
	if (ConvertingValue)
	{
		AddDebugMessage("Conversion of given value to type " + FunctionDefinition->FunctionData.ParameterData[ArgumentIndex].Type 
			+ " for argument " + FunctionDefinition->FunctionData.ParameterData[ArgumentIndex].Name 
			+ " in function " + FunctionDefinition->FunctionData.FunctionName + " completed.");
		ConvertingValue = false;
		Values[ArgumentIndex] = GetCodeRunner()->GetValue();
		ArgumentIndex++;
	}


	// Loop through values and convert them if necessary
	while (ArgumentIndex < Values.Num())
	{
		FString currentType = Values[ArgumentIndex]->Type;
		FString wantedType = FunctionDefinition->FunctionData.ParameterData[ArgumentIndex].Type;
		if (wantedType == "element type") wantedType = currentType;
		AddDebugMessage("For function " + FunctionDefinition->FunctionData.FunctionName + " argument " + FunctionDefinition->FunctionData.ParameterData[ArgumentIndex].Name
			+ " is of type " + wantedType + ". Passed value is of type " + currentType + ".");

		if (currentType == wantedType || GetCodeRunner()->GetSymbolTable()->IsChildOfByName(currentType, wantedType))
		{
			AddDebugMessage("No need to convert passed value.");
			ArgumentIndex++;
			continue;
		}

		UAST_FunctionDefinition* converter = GetCodeRunner()->GetSymbolTable()->GetImplicitConverterByName(currentType, wantedType);
		AddDebugMessage("Conversion required. Converting " + currentType + " to " + wantedType + " using " + converter->FunctionData.FunctionName + " converter.");
		ConvertingValue = true;
		URTS_ChainedFunctionCall* converterRTS = NewObject<URTS_ChainedFunctionCall>(GetCodeRunner());
		TArray<UValue*> ValueToConvert;
		ValueToConvert.Add(Values[ArgumentIndex]);
		converterRTS->Init(GetCodeRunner());
		converterRTS->SetData(converter, Owner, ValueToConvert);
		GetCodeRunner()->AddRTS(converterRTS);
		StepCompleted();
		return;
	}


	AddDebugMessage("All type conversions for function " + FunctionDefinition->FunctionData.FunctionName + " completed.");
	GetCodeRunner()->AddStackFrame(Owner);
	for (int i = 0; i < Values.Num(); ++i)
	{
		// Duplicate value before passing it, if it is not passed by reference
		UValue* ValueToPass;
		if (FunctionDefinition->FunctionData.ParameterData[i].IsPassByReference)
		{
			AddDebugMessage("Argument " + FunctionDefinition->FunctionData.ParameterData[i].Name
				+ " is passed by reference. Passing value.");
			ValueToPass = Values[i];
		}
		else
		{
			AddDebugMessage("Argument " + FunctionDefinition->FunctionData.ParameterData[i].Name
				+ " is not passed by reference. Duplicating value before passing it to the function.");
			ValueToPass = Values[i]->Duplicate();
		}

		FString name = FunctionDefinition->FunctionData.ParameterData[i].Name;
		GetCodeRunner()->AddVariable(name, ValueToPass);
	}

	AddDebugMessage("Running function " + FunctionDefinition->FunctionData.FunctionName + " with properly converted types.");
	AddRTSToCodeRunner(FunctionDefinition);
	Finished();
}

void URTS_ChainedFunctionCall::SetData(UAST_FunctionDefinition* functionDefinition, UValue* owner, TArray<UValue*> values)
{
	FunctionDefinition = functionDefinition;
	Owner = owner;
	Values = values;
}

