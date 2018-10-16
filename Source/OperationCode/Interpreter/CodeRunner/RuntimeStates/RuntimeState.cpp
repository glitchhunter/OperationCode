// Fill out your copyright notice in the Description page of Project Settings.

#include "RuntimeState.h"
#include "Interpreter/Parser/AST/AST_Node.h"


UWorld* URuntimeState::GetWorld() const
{
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		return GetOuter()->GetWorld();
	}
	else
	{
		return nullptr;
	}
}

void URuntimeState::StepCompleted()
{
	GetCodeRunner()->RTSStepCompleted();
}

void URuntimeState::Finished()
{
	IsCompleted = true;
	GetCodeRunner()->RTSStepCompleted();
}

void URuntimeState::AddRTSToCodeRunner(UAST_Node* Node)
{
	GetCodeRunner()->AddRTS(Node->CreateRuntimeState(GetCodeRunner()));
}

void URuntimeState::AddScope()
{
	AddedScope = true;
	GetCodeRunner()->AddScope();
}

void URuntimeState::AddDebugMessage(FString Message)
{
	GetCodeRunner()->AddDebugMessage(Message);
}

void URuntimeState::ThrowRuntimeError(FString ErrorMessage)
{
	GetCodeRunner()->RuntimeError(ErrorMessage);
}
