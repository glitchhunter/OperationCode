// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeRunner.h"
#include "Interpreter/CodeRunner/RuntimeStates/RuntimeState.h"
#include "Interpreter/Parser/AST/AST_Node.h"
#include "Interpreter/Parser/AST/Definition/AST_FunctionDefinition.h"
#include "Interpreter/CodeRunner/Values/Value.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/BoolInstance.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/FloatInstance.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/IntInstance.h"
#include "Interpreter/CodeRunner/Values/PredefinedClasses/StringInstance.h"
#include "Interpreter/CodeRunner/Values/TypeValue.h"
#include "Interpreter/CodeRunner/RuntimeStates/Implicit/RTS_StaticInitializer.h"
#include "Interpreter/SemanticAnalysis/SymbolTable.h"
#include "Runtime/Engine/Classes/Engine/World.h"



bool UCodeRunner::HasStackFrame() const
{
	return Stack.Num() > 0;
}

FStackFrame UCodeRunner::GetStackFrame() const
{
	return Stack.Top();
}

bool UCodeRunner::HasRTS() const
{
	if (!HasStackFrame()) return false;

	return GetStackFrame().RuntimeStates.Num() > 0;
}

URuntimeState* UCodeRunner::GetRTS() const
{
	if (!HasRTS()) return nullptr;

	return GetStackFrame().RuntimeStates.Top();
}

bool UCodeRunner::HasScope() const
{
	if (!HasStackFrame()) return false;

	return GetStackFrame().Scopes.Num() > 0;
}

FScope UCodeRunner::GetScope() const
{
	return GetStackFrame().Scopes.Top();
}

void UCodeRunner::SetValue(UValue* Value)
{
	ReturnedValue = Value;
}

UValue* UCodeRunner::GetValue() const
{
	return ReturnedValue;
}

UValue* UCodeRunner::GetOwner() const 
{
	if (!HasStackFrame()) return nullptr;

	return GetStackFrame().Owner;
}




void UCodeRunner::AddScope()
{
	if (!HasStackFrame()) return;

	Stack.Top().Scopes.Add(FScope());
}

void UCodeRunner::PopScope()
{
	if (!HasScope()) return;

	Stack.Top().Scopes.Pop();
}

void UCodeRunner::AddStackFrame(UValue* StackOwner)
{
	FStackFrame SF;
	SF.Owner = StackOwner;
	SF.Scopes.Add(FScope());
	Stack.Add(SF);
}

void UCodeRunner::PopStackFrame()
{
	if (!HasStackFrame()) return;
	Stack.Pop();
	AddDebugMessage("----Removing stack frame.");
}

void UCodeRunner::AddVariable(FString Varname, UValue* Value)
{
	if (!HasScope()) return;

	Stack.Top().Scopes.Top().ValuesInScope.Add(Varname, Value);
}

void UCodeRunner::AddRTS(URuntimeState* RuntimeState)
{
	AddDebugMessage("----Adding " + RuntimeState->GetName() + " to RTS stack.");

	if (!HasStackFrame()) return;

	Stack.Top().RuntimeStates.Add(RuntimeState);
}

void UCodeRunner::PopRTS()
{
	if (!HasRTS()) return;

	if (GetRTS()->HasAddedScope()) PopScope();
	URuntimeState* top = Stack.Top().RuntimeStates.Top();
	Stack.Top().RuntimeStates.Pop();
	AddDebugMessage("----Removing " + top->GetName() + " from RTS stack.");
}

// Visual studio is helpfull enough to optimize something in my last loop away when run in non-debug mode,
// making the whole thing crash. Thanks, Visual studio, debuging this without the debugger was fun.
#pragma optimize( "", on )
UValue* UCodeRunner::GetVariable(FString VarName)
{
	// Check for variable in this call stack
	for (int i = GetStackFrame().Scopes.Num() - 1; i >= 0; --i)
	{
		UValue** var = Stack.Top().Scopes[i].ValuesInScope.Find(VarName);
		if (var) return *var;
	}

	// Check for variables that live in this owner
	if (GetOwner())
	{
		UValue* var = GetOwner()->GetVariable(VarName);
		if (var) return var;
	}

	// Check for globaly declared variables in the lowest stack frame
	// Only first three scopes are considered global
	for (int i = 2; i >= 0; --i)
	{
		UValue** var = Stack[0].Scopes[i].ValuesInScope.Find(VarName);
		if (var) return *var;
	}


	return nullptr;
}
#pragma optimize( "", off )





void UCodeRunner::RunNextRTSStep()
{
	if (CurrentCodeState != ECodeState::WaitingForNextStep) return;

	StepCounter++;

	while (HasRTS() && GetRTS()->GetIsCompleted())
	{
		PopRTS();
	}

	if (!HasRTS())
	{
		CodeCompleted();
		return;
	}

	CurrentCodeState = ECodeState::Running;
	GetRTS()->RunStep();
}

void UCodeRunner::RTSStepCompleted()
{
	if (Aborting)
	{
		CurrentCodeState = ECodeState::NotRunning;
		Aborting = false;
		Stack.Empty();
		Interpreter = nullptr;
		return;
	}

	CurrentCodeState = ECodeState::WaitingForNextStep;
	if (AutoRun)
	{
		if (StepCounter <= MaxStepsPerFrame)
		{
			RunNextRTSStep();
			return;
		}
		else
		{
			StepCounter = 0;
			FrameDelay();
			return;
		}
	}
	else
	{
		StepCounter = 0;
	}
}

void UCodeRunner::CodeCompleted()
{
	if (CurrentCodeState == ECodeState::NotRunning) return;

	CurrentCodeState = ECodeState::NotRunning;
	GetInterpreter()->CodeCompleted();
	UWorld* world = GetWorld();
	if (!world) return;

	// Clear frame delay timer handle, just in case
	world->GetTimerManager().ClearTimer(FrameDelayTimerHandle);
}

void UCodeRunner::RunCode(UAST_Node* RootNode, USymbolTable* symbolTable)
{
	if (CurrentCodeState != ECodeState::NotRunning) return;
	CurrentCodeState = ECodeState::WaitingForNextStep;
	SymbolTable = symbolTable;
	StepCounter = 0;

	AddStackFrame(SymbolTable->TopOwner);
	AddRTS(RootNode->CreateRuntimeState(this));
	URTS_StaticInitializer* statInit = NewObject<URTS_StaticInitializer>(this);
	statInit->Init(this);
	AddRTS(statInit);
	RunNextRTSStep();
}


UTypeValue* UCodeRunner::GetTypeValue(FString Type)
{
	UTypeValue** val = TypeValues.Find(Type);
	if (!val) return nullptr;

	return *val;
}

void UCodeRunner::AddTypeValue(UTypeValue* NewTypeValue)
{
	TypeValues.Add(NewTypeValue->Type, NewTypeValue);
}



void UCodeRunner::FrameDelay()
{
	// Every action can require multiple steps. Even though I did my best to try and keep that part of the code simple enough so VS could optimize
	// it away with tail recursion, that did not happen. Even if it did, relaying on compiler to fix code issues is bad design.
	// Therefore I am adding a frame delay after a certain amount of steps activated. That should negate the stack overflow problems.

	UWorld* world = GetWorld();
	if (!world)
	{
		UE_LOG(LogTemp, Error, TEXT("Attempting to create a frame delay, but no valid world reference is available."));
		return;
	}

	// In blueprints, having a delay of 0 skips a single frame. Unfortunately, timers (at least in c++) do not do that.
	
	world->GetTimerManager().SetTimer(FrameDelayTimerHandle, this, &UCodeRunner::RunNextRTSStep, SMALL_NUMBER);
}

void UCodeRunner::AbortExecution()
{
	Aborting = true;
}


void UCodeRunner::RuntimeError(FString ErrorMessage)
{
	Interpreter->AbortDueToRuntimeError(ErrorMessage);
}


