// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_FunctionDefinition.h"
#include "Interpreter/Parser/AST/Definition/AST_FunctionDefinition.h"
#include "Interpreter/Parser/AST/AST_Scope.h"


void URTS_FunctionDefinition::RunStep()
{
	// Functions stack frame and initial scope with parameters as variables
	// are already created by function call.
	if (!ScopeCompleted)
	{
		AddDebugMessage("Preparing to run scope for " + FunctionDefinition->FunctionData.FunctionName + ".");
		// Custom function definitions should override RunStep to add their own behavior
		AddRTSToCodeRunner(FunctionDefinition->Scope);
		ScopeCompleted = true;
		StepCompleted();
		return;
	}

	// If we reach this code, then the function completed without reaching a return statement.
	// This means that this is a void function. Pop the stack frame and clear return value.
	AddDebugMessage("Function " + FunctionDefinition->FunctionData.FunctionName + "completed.");
	UValue* own = GetCodeRunner()->GetOwner();
	GetCodeRunner()->PopStackFrame();
	// Special case if this is a constructor
	if (GetCodeRunner()->GetSymbolTable()->ClassNames.Contains(FunctionDefinition->FunctionData.FunctionName))
		GetCodeRunner()->SetValue(own);
	else GetCodeRunner()->SetValue(nullptr);
	Finished();
}

UAST_Node* URTS_FunctionDefinition::GetNode() const
{
	return FunctionDefinition;
}





UValue* URTS_FunctionDefinition::GetVariable(FString VarName)
{
	return GetCodeRunner()->GetVariable(VarName);
}

UBoolInstance* URTS_FunctionDefinition::GetBoolVariable(FString VarName)
{
	UBoolInstance* boolInstance = Cast<UBoolInstance>(GetVariable(VarName));
	if (!boolInstance) return nullptr;
	return boolInstance;
}

bool URTS_FunctionDefinition::GetBoolValue(FString VarName)
{
	UBoolInstance* boolInstance = GetBoolVariable(VarName);
	if (!boolInstance) return false;
	return boolInstance->Value;
}

UIntInstance* URTS_FunctionDefinition::GetIntVariable(FString VarName)
{
	UIntInstance* intInstance = Cast<UIntInstance>(GetVariable(VarName));
	if (!intInstance) return nullptr;
	return intInstance;
}

int32 URTS_FunctionDefinition::GetIntValue(FString VarName)
{
	UIntInstance* intInstance = GetIntVariable(VarName);
	if (!intInstance) return 0;
	return intInstance->Value;
}

UFloatInstance* URTS_FunctionDefinition::GetFloatVariable(FString VarName)
{
	UFloatInstance* floatInstance = Cast<UFloatInstance>(GetVariable(VarName));
	if (!floatInstance) return nullptr;
	return floatInstance;
}

float URTS_FunctionDefinition::GetFloatValue(FString VarName)
{
	UFloatInstance* floatInstance = GetFloatVariable(VarName);
	if (!floatInstance) return 0.0f;
	return floatInstance->Value;
}

UStringInstance* URTS_FunctionDefinition::GetStringVariable(FString VarName)
{
	UStringInstance* stringInstance = Cast<UStringInstance>(GetVariable(VarName));
	if (!stringInstance) return nullptr;
	return stringInstance;
}

FString URTS_FunctionDefinition::GetStringValue(FString VarName)
{
	UStringInstance* stringInstance = GetStringVariable(VarName);
	if (!stringInstance) return "";
	return stringInstance->Value;
}

UValue* URTS_FunctionDefinition::GetOwner()
{
	return GetCodeRunner()->GetOwner();
}



