// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_InstanceCreator.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/BoolInstance.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/FloatInstance.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/IntInstance.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/StringInstance.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/ArrayInstance.h"
#include "Interpreter/Parser/AST/Definition/AST_ClassDefinition.h"
#include "Interpreter/Parser/AST/Definition/AST_VariableDefinition.h"
#include "Interpreter/CodeRunner/Values/Variables.h"
#include "Interpreter/CodeRunner/RuntimeStates/Implicit/RTS_ChainedFunctionCall.h"

void URTS_InstanceCreator::RunStep()
{
	if (ConstructorStarted)
	{
		GetCodeRunner()->SetValue(NewValue);
		Finished();
		return;
	}


	// Create the value if it doesn't exist already
	if (!NewValue)
	{
		if (IsArray)
		{
			NewValue = CreateArrayValue(GetCodeRunner(), Type, TArray<UValue*>());
			GetCodeRunner()->SetValue(NewValue);
			Finished();
			return;
		}

		// Try to create a predefined type
		NewValue = CreatePredefinedType(GetCodeRunner(), Type);
		if (NewValue)
		{
			GetCodeRunner()->SetValue(NewValue);
			Finished();
			return;
		}


		UAST_ClassDefinition** ClassPointer = GetCodeRunner()->GetSymbolTable()->ClassNames.Find(Type);
		if (!ClassPointer)
		{
			UE_LOG(LogTemp, Fatal, TEXT("Trying to create a value of unknown type $s."), *Type);
			return;
		}
		Class = *ClassPointer;
		NewValue = NewObject<UValue>(GetCodeRunner());
		NewValue->Init(Type, GetCodeRunner());
		NewValue->CreateVariables();
		AddDebugMessage("Creating a new value of type " + Type + ".");
	}

	if (ExpectingInitExpression)
	{
		UAST_VariableDefinition* currentVar = Class->VariableDefinitions[VariableIndex];
		if (!ValueAssigned)
		{
			TArray<FParamSignature> ParamSigs;
			ParamSigs.Add(FParamSignature(currentVar->Type, currentVar->IsArray));
			ParamSigs.Add(FParamSignature(GetCodeRunner()->GetValue()->Type, GetCodeRunner()->GetValue()->IsA<UArrayInstance>()));

			UValue* val = CreatePredefinedType(GetCodeRunner(), currentVar->Type);
			if (!val)
			{
				val = NewObject<UValue>(NewValue);
				val->Init(currentVar->Type, GetCodeRunner());
				val->CreateVariables();
			}
			TArray<UValue*> AssignValues;
			AssignValues.Add(val);
			AssignValues.Add(GetCodeRunner()->GetValue());

			UAST_FunctionDefinition* AssignOperator = GetCodeRunner()->GetSymbolTable()->GetOverloadedOperator(FFunctionSignature("operator =", ParamSigs));
			URTS_ChainedFunctionCall* chainedFunctionCall = NewObject<URTS_ChainedFunctionCall>(GetCodeRunner());
			chainedFunctionCall->Init(GetCodeRunner());
			chainedFunctionCall->SetData(AssignOperator, nullptr, AssignValues);
			GetCodeRunner()->AddRTS(chainedFunctionCall);
			ValueAssigned = true;
			ExpectingInitExpression = false;
			StepCompleted();
			return;
		}
		NewValue->Variables->Variables.Add(currentVar->Name, GetCodeRunner()->GetValue());
		VariableIndex++;
	}

	// Loop through all class instance variables and create them
	while (VariableIndex < Class->VariableDefinitions.Num())
	{
		UAST_VariableDefinition* currentVar = Class->VariableDefinitions[VariableIndex];
		// Do not create static variables for instances. Those are handeled at the start of the RunCode().
		if (currentVar->IsStatic)
		{
			VariableIndex++;
			continue;
		}

		if (!currentVar->InitExpression)
		{
			if (GetCodeRunner()->GetSymbolTable()->IsInstanceUnique(GetCodeRunner()->GetSymbolTable()->ClassNames[currentVar->Type]))
			{
				// A nullable value with no init expression is a null value
				NewValue->Variables->Variables.Add(currentVar->Type, CreateNullValue(GetCodeRunner(), currentVar->Type));
				VariableIndex++;
				continue;
			}
			else
			{
				URTS_InstanceCreator* instanceCreator = NewObject<URTS_InstanceCreator>(GetCodeRunner());
				instanceCreator->Init(GetCodeRunner());
				instanceCreator->SetValues(currentVar->Type, currentVar->IsArray, TArray<UValue*>());
				ExpectingInitExpression = true;
				GetCodeRunner()->AddRTS(instanceCreator);
				StepCompleted();
				return;
			}
		}
		else
		{
			// Run Init expression
			AddRTSToCodeRunner(currentVar->InitExpression);
			ExpectingInitExpression = true;
			StepCompleted();
			return;
		}
	}

	TArray<FParamSignature> paramSigs;
	for (UValue* ConstrParam : ConstructorParameters)
	{
		paramSigs.Add(FParamSignature(ConstrParam->Type, ConstrParam->IsA<UArrayInstance>()));
	}
	UAST_FunctionDefinition* constructor = GetCodeRunner()->GetSymbolTable()->GetConstructor(NewValue->Type, paramSigs);
	if (!constructor)
	{
		GetCodeRunner()->SetValue(NewValue);
		Finished();
		return;
	}

	URTS_ChainedFunctionCall* cfc = NewObject<URTS_ChainedFunctionCall>(GetCodeRunner());
	cfc->Init(GetCodeRunner());
	cfc->SetData(constructor, NewValue, ConstructorParameters);
	GetCodeRunner()->AddRTS(cfc);
	ConstructorStarted = true;
	StepCompleted();
}

void URTS_InstanceCreator::SetValues(FString type, bool isArray, TArray<UValue*> constructorParameters)
{
	Type = type;
	IsArray = isArray;
	ConstructorParameters = constructorParameters;
}

UBoolInstance* URTS_InstanceCreator::CreateBoolValue(UCodeRunner* activeCodeRunner, bool Value /* = false */)
{
	UBoolInstance* boolValue = NewObject<UBoolInstance>(activeCodeRunner);
	boolValue->Init("bool", activeCodeRunner);
	boolValue->Value = Value;
	return boolValue;
}

UIntInstance* URTS_InstanceCreator::CreateIntValue(UCodeRunner* activeCodeRunner, int32 Value /* = 0 */)
{
	UIntInstance* intValue = NewObject<UIntInstance>(activeCodeRunner);
	intValue->Init("int", activeCodeRunner);
	intValue->Value = Value;
	return intValue;
}

UFloatInstance* URTS_InstanceCreator::CreateFloatValue(UCodeRunner* activeCodeRunner, float Value /* = 0.0f */)
{
	UFloatInstance* floatValue = NewObject<UFloatInstance>(activeCodeRunner);
	floatValue->Init("float", activeCodeRunner);
	floatValue->Value = Value;
	return floatValue;
}

UStringInstance* URTS_InstanceCreator::CreateStringValue(UCodeRunner* activeCodeRunner, FString Value /* = "" */)
{
	UStringInstance* stringValue = NewObject<UStringInstance>(activeCodeRunner);
	stringValue->Init("string", activeCodeRunner);
	stringValue->Value = Value;
	return stringValue;
}

UValue* URTS_InstanceCreator::CreateNullValue(UCodeRunner* activeCodeRunner, FString type)
{
	UValue* val = NewObject<UValue>(activeCodeRunner);
	val->Init(type, activeCodeRunner);
	if (!val->IsNullable())
	{
		UE_LOG(LogTemp, Fatal, TEXT("Attempted to create a null value of type %s, which cannot be null."), *type);
	}
	return val;
}

UArrayInstance* URTS_InstanceCreator::CreateArrayValue(UCodeRunner* activeCodeRunner, FString type, TArray<UValue*> Values /* = TArray<UValue*>() */)
{
	UArrayInstance* arrayInstance = NewObject<UArrayInstance>(activeCodeRunner);
	arrayInstance->Init(type, activeCodeRunner);
	arrayInstance->Value = Values;
	return arrayInstance;
}

UValue* URTS_InstanceCreator::CreatePredefinedType(UCodeRunner* activeCodeRunner, FString type)
{
	if (type == "bool") return CreateBoolValue(activeCodeRunner);
	if (type == "int") return CreateIntValue(activeCodeRunner);
	if (type == "float") return CreateFloatValue(activeCodeRunner);
	if (type == "string") return CreateStringValue(activeCodeRunner);
	return nullptr;
}




