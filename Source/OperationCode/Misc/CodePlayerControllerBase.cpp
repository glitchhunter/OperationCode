// Fill out your copyright notice in the Description page of Project Settings.

#include "CodePlayerControllerBase.h"
#include "Interpreter/Interpreter.h"
#include "Interpreter/CodeRunner/CodeRunner.h"
#include "Interpreter/Parser/AST/AST_Basic.h"
#include "Interpreter/SemanticAnalysis/Phases/Limitations/SemanticLimitation.h"
#include "Interpreter/CodeRunner/Values/Value.h"
#include "Misc/CodeLevelScript.h"


ACodePlayerControllerBase::ACodePlayerControllerBase()
{
	Interp = CreateDefaultSubobject<UInterpreter>(TEXT("Interpreter"));
}


void ACodePlayerControllerBase::BeginPlay()
{
	// One day, due to unknown arcane magic, somewhere along the way between constructor and begin play, interpreter got nulled.
	if (!GetInterpreter())
	{
		Interp = NewObject<UInterpreter>(this);
		UE_LOG(LogTemp, Error, TEXT("Interpreter still nulled after constructor."));
	}
	GetInterpreter()->OnRuntimeMessageSent.AddDynamic(this, &ACodePlayerControllerBase::OnRuntimeMessageSent);
	GetInterpreter()->OnRuntimeLogSent.AddDynamic(this, &ACodePlayerControllerBase::OnRuntimeLogSent);
	GetInterpreter()->OnStaticInitCompleted.AddDynamic(this, &ACodePlayerControllerBase::OnStaticinitCompleted);
	GetInterpreter()->OnCodeCompleted.AddDynamic(this, &ACodePlayerControllerBase::OnCodeCompleted);
	GetInterpreter()->OnRuntimeError.AddDynamic(this, &ACodePlayerControllerBase::OnRuntimeError);

	Super::BeginPlay();
}


bool ACodePlayerControllerBase::Compile_Implementation(const FString& SourceCode)
{
	if (!CanCompile()) return false;

	Clear();
	CompileData = GetInterpreter()->Compile(SourceCode, GetPrecompiledData(), GetTopOwner());
	return GetInterpreter()->IsCompileValid(CompileData);
}

bool ACodePlayerControllerBase::CanCompile()
{
	if (!GetInterpreter()) return false;
	if (!GetInterpreter()->GetCodeRunner()) return true;
	return GetInterpreter()->GetCodeRunner()->GetCurrentCodeState() == ECodeState::NotRunning;
}

void ACodePlayerControllerBase::RunCode(bool AutoRun)
{
	if (!CanRunCode()) return;

	GetInterpreter()->RunCode(CompileData.AST, CompileData.SymbolTable, AutoRun, MaxSteps);
}

bool ACodePlayerControllerBase::CanRunCode()
{
	if (!GetInterpreter()) return false;
	if (GetInterpreter()->GetCurrentState() == EInterpreterState::AnalysisCompleted) return true;
	return (GetInterpreter()->GetCodeRunner() && GetInterpreter()->GetCodeRunner()->GetCurrentCodeState() != ECodeState::Running && GetInterpreter()->GetCurrentState() == EInterpreterState::RunningCode);
}

void ACodePlayerControllerBase::Clear_Implementation()
{
	ClearCompileData();
	GetInterpreter()->Clear();
}

void ACodePlayerControllerBase::SetMaxSteps(int32 NewMaxSteps)
{
	MaxSteps = NewMaxSteps;
	if (GetInterpreter() && GetInterpreter()->GetCodeRunner()) GetInterpreter()->GetCodeRunner()->MaxStepsPerFrame = MaxSteps;
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


