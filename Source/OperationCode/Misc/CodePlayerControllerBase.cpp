// Fill out your copyright notice in the Description page of Project Settings.

#include "CodePlayerControllerBase.h"
#include "Interpreter/Interpreter.h"
#include "Interpreter/CodeRunner/CodeRunner.h"
#include "Interpreter/Parser/AST/AST_Basic.h"
#include "Interpreter/SemanticAnalysis/Phases/Limitations/SemanticLimitation.h"
#include "Interpreter/CodeRunner/Values/Value.h"
#include "Misc/CodeLevelScript.h"



void ACodePlayerControllerBase::BeginPlay()
{
	Interpreter = NewObject<UInterpreter>(this);
	Interpreter->OnRuntimeMessageSent.AddDynamic(this, &ACodePlayerControllerBase::OnRuntimeMessageSent);
	Interpreter->OnRuntimeLogSent.AddDynamic(this, &ACodePlayerControllerBase::OnRuntimeLogSent);
	Interpreter->OnStaticInitCompleted.AddDynamic(this, &ACodePlayerControllerBase::OnStaticinitCompleted);
	Interpreter->OnCodeCompleted.AddDynamic(this, &ACodePlayerControllerBase::OnCodeCompleted);
	Interpreter->OnRuntimeError.AddDynamic(this, &ACodePlayerControllerBase::OnRuntimeError);

	Super::BeginPlay();
}


bool ACodePlayerControllerBase::Compile_Implementation(const FString& SourceCode)
{
	if (!CanCompile()) return false;

	Clear();
	CompileData = Interpreter->Compile(SourceCode, GetPrecompiledData(), GetTopOwner(), Limitations);
	return Interpreter->IsCompileValid(CompileData);
}

bool ACodePlayerControllerBase::CanCompile()
{
	if (!Interpreter) return false;
	if (!Interpreter->GetCodeRunner()) return true;
	return Interpreter->GetCodeRunner()->GetCurrentCodeState() == ECodeState::NotRunning;
}

void ACodePlayerControllerBase::RunCode(bool AutoRun)
{
	if (!CanRunCode()) return;

	Interpreter->RunCode(CompileData.AST, CompileData.SymbolTable, AutoRun, MaxSteps);
}

bool ACodePlayerControllerBase::CanRunCode()
{
	if (!Interpreter) return false;
	if (Interpreter->GetCurrentState() == EInterpreterState::AnalysisCompleted) return true;
	return (Interpreter->GetCodeRunner() && Interpreter->GetCodeRunner()->GetCurrentCodeState() != ECodeState::Running && Interpreter->GetCurrentState() == EInterpreterState::RunningCode);
}

void ACodePlayerControllerBase::Clear_Implementation()
{
	ClearCompileData();
	Interpreter->Clear();
}

void ACodePlayerControllerBase::SetMaxSteps(int32 NewMaxSteps)
{
	MaxSteps = NewMaxSteps;
	if (Interpreter && Interpreter->GetCodeRunner()) Interpreter->GetCodeRunner()->MaxStepsPerFrame = MaxSteps;
}

UAST_Basic* ACodePlayerControllerBase::GetPrecompiledData_Implementation()
{
	UAST_Basic* basic = NewObject<UAST_Basic>(this, BasicType);
	basic->PredefinedClasses.Append(ExtraClasses);
	basic->PredefinedFunctions.Append(ExtraFunctions);
	return basic;
}

void ACodePlayerControllerBase::AddClass_Implementation(UAST_ClassDefinition* ClassDefinition)
{
	if (!ClassDefinition) return;

	if (IsClassAlreadyDefined(ClassDefinition->Name))
	{
		// Class is already added, just increase the counter
		ClassCounter[ClassDefinition->Name]++;
		return;
	}

	// Add new class
	ExtraClasses.Add(ClassDefinition);
	ClassCounter.Add(ClassDefinition->Name, 1);
}

void ACodePlayerControllerBase::RemoveClass_Implementation(const FString& ClassName)
{
	if (!ClassCounter.Contains(ClassName)) return;

	// remove class from list
	for (int i = 0; i < ExtraClasses.Num(); ++i)
	{
		if (ExtraClasses[i]->Name == ClassName)
		{
			ExtraClasses.RemoveAt(i);
			break;
		}
	}

	// Decrease counter
	if (ClassCounter[ClassName] <= 1)
		ClassCounter.Remove(ClassName);
	else ClassCounter[ClassName]--;
}

bool ACodePlayerControllerBase::IsClassAlreadyDefined(const FString& ClassName)
{
	return ClassCounter.Contains(ClassName);
}

void ACodePlayerControllerBase::AddFunction_Implementation(UAST_FunctionDefinition* FunctionDefinition)
{
	if (!FunctionDefinition) return;

	if (FunctionCounter.Contains(FunctionDefinition->FunctionData.GetSignature()))
	{
		// Function is already added, just increase the counter
		FunctionCounter[FunctionDefinition->FunctionData.GetSignature()]++;
		return;
	}

	// Add new function
	ExtraFunctions.Add(FunctionDefinition);
	FunctionCounter.Add(FunctionDefinition->FunctionData.GetSignature(), 1);
}

void ACodePlayerControllerBase::RemoveFunction_Implementation(const FFunctionSignature& FunctionSig)
{
	if (!FunctionCounter.Contains(FunctionSig)) return;

	// remove function from list
	for (int i = 0; i < ExtraFunctions.Num(); ++i)
	{
		if (ExtraFunctions[i]->FunctionData.GetSignature() == FunctionSig)
		{
			ExtraFunctions.RemoveAt(i);
			break;
		}
	}

	// Decrease counter
	if (FunctionCounter[FunctionSig] <= 1)
		FunctionCounter.Remove(FunctionSig);
	else FunctionCounter[FunctionSig]--;
}


