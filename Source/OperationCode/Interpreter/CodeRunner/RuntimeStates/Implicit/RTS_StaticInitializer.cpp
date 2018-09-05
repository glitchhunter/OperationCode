// Fill out your copyright notice in the Description page of Project Settings.

#include "RTS_StaticInitializer.h"
#include "Interpreter/Parser/AST/Definition/AST_ClassDefinition.h"
#include "Interpreter/Parser/AST/Definition/AST_VariableDefinition.h"
#include "Interpreter/CodeRunner/Values/TypeValue.h"

void URTS_StaticInitializer::RunStep()
{
	if (!ClassesCached)
	{
		for (auto it = GetCodeRunner()->GetSymbolTable()->ClassNames.CreateConstIterator(); it; ++it)
		{
			AllClasses.Add(it->Value);
			UTypeValue* currentTypeVal = NewObject<UTypeValue>(GetCodeRunner());
			currentTypeVal->Init(it->Key, GetCodeRunner());
			GetCodeRunner()->AddTypeValue(currentTypeVal);
		}
		ClassesCached = true;
	}

	if (ExpectingValueReturn)
	{
		ExpectingValueReturn = false;
		UAST_ClassDefinition* currentClass = AllClasses[ClassIndex];
		GetCodeRunner()->GetTypeValue(currentClass->Name)->AddVariable(currentClass->VariableDefinitions[VariableIndex]->Name, GetCodeRunner()->GetValue());
		VariableIndex++;
	}

	while (ClassIndex < AllClasses.Num())
	{
		UAST_ClassDefinition* currentClass = AllClasses[ClassIndex];

		while (VariableIndex < currentClass->VariableDefinitions.Num())
		{
			UAST_VariableDefinition* currentVar = currentClass->VariableDefinitions[VariableIndex];
			if (!currentVar->IsStatic)
			{
				// Skip non static variables
				VariableIndex++;
				continue;
			}

			// Create variable
			URTS_InstanceCreator* instanceCreator = NewObject<URTS_InstanceCreator>(GetCodeRunner());
			instanceCreator->Init(GetCodeRunner());
			instanceCreator->SetValues(currentVar->Type, currentVar->IsArray, TArray<UValue*>());
			GetCodeRunner()->AddRTS(instanceCreator);
			ExpectingValueReturn = true;
			StepCompleted();
			return;
		}
		VariableIndex = 0;
		ClassIndex++;
	}

	GetCodeRunner()->GetInterpreter()->OnStaticInitCompleted.Broadcast();
	Finished();
}



