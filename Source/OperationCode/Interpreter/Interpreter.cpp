// Fill out your copyright notice in the Description page of Project Settings.

#include "Interpreter.h"
#include "Interpreter/Lexer/Lexer.h"
#include "Interpreter/Parser/Parser.h"
#include "Interpreter/SemanticAnalysis/SemanticAnalysis.h"
#include "Interpreter/CodeRunner/CodeRunner.h"
#include "Interpreter/Parser/AST/AST_Basic.h"
#include "Interpreter/Parser/AST/AST_Main.h"


UWorld* UInterpreter::GetWorld() const
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

void UInterpreter::Clear()
{
	CodeRunner = nullptr;
	Errors.Empty();
	CurrentState = EInterpreterState::Idle;
}

FCompileData UInterpreter::Compile(FString SourceCode, UAST_Basic* RootNode, UValue* TopOwner)
{
	FCompileData CompileData;
	if (CurrentState != EInterpreterState::Idle)
	{
		CompileData.Errors.Messeges.Add("Cannot compile at this time.");
		CompileData.Errors.Phase = CurrentState;
		OnCompiled.Broadcast(CompileData);
		return CompileData;
	}

	TArray<UToken*> tokens = Lex(SourceCode);
	CompileData.Tokens = tokens;
	if (HasErrors())
	{
		CompileData.Errors.Messeges = GetErrors();
		CompileData.Errors.Phase = CurrentState;
		OnCompiled.Broadcast(CompileData);
		return CompileData;
	}

	TArray<UAST_Node*> Nodes = Parse(tokens);
	if (HasErrors())
	{
		CompileData.Errors.Messeges = GetErrors();
		CompileData.Errors.Phase = CurrentState;
		OnCompiled.Broadcast(CompileData);
		return CompileData;
	}

	UAST_Main* mainNode = NewObject<UAST_Main>(this);
	RootNode->Main = mainNode;

	for (UAST_Node* currentNode : Nodes)
	{
		mainNode->Children.Add(currentNode);
	}

	CompileData.AST = RootNode;
	USymbolTable* symbolTable = Analyse(RootNode, TopOwner);
	CompileData.SymbolTable = symbolTable;
	if (HasErrors())
	{
		CompileData.Errors.Messeges = GetErrors();
		CompileData.Errors.Phase = CurrentState;
		OnCompiled.Broadcast(CompileData);
		return CompileData;
	}

	CompileData.Warnings = Warnings;
	OnCompiled.Broadcast(CompileData);
	return CompileData;
}

TArray<UToken*> UInterpreter::Lex(FString SourceCode)
{
	if (CurrentState != EInterpreterState::Idle) return TArray<UToken*>();

	ULexer* Lexer = NewObject<ULexer>(this);
	Lexer->Init(this);

	CurrentState = EInterpreterState::LexingCompleted;
	return Lexer->Tokenize(SourceCode);
}
TArray<UAST_Node*> UInterpreter::Parse(TArray<UToken*> Tokens)
{
	if (CurrentState != EInterpreterState::LexingCompleted) return TArray<UAST_Node*>();

	UParser* Parser = NewObject<UParser>(this);
	Parser->Init(this);

	CurrentState = EInterpreterState::ParsingCompleted;
	return Parser->ParseTokens(Tokens);
}

USymbolTable* UInterpreter::Analyse(UAST_Node* RootNode, UValue* TopOwner)
{
	if (CurrentState != EInterpreterState::ParsingCompleted) return nullptr;

	USemanticAnalysis* SemAnalysis = NewObject<USemanticAnalysis>(this);
	SemAnalysis->Init(this);
	SemAnalysis->Limitations = Limitations;

	CurrentState = EInterpreterState::AnalysisCompleted;
	return SemAnalysis->AnalyseAST(RootNode, TopOwner);
}

void UInterpreter::RunCode(UAST_Node* RootNode, USymbolTable* symbolTable, bool AutoRun, int32 MaxSteps)
{
	if (CurrentState == EInterpreterState::RunningCode)
	{
		CodeRunner->AutoRun = AutoRun;
		CodeRunner->RunNextRTSStep();
		return;
	}

	if (CurrentState != EInterpreterState::AnalysisCompleted) return;

	CodeRunner = NewObject<UCodeRunner>(this);
	CodeRunner->Init(this);
	CodeRunner->AutoRun = AutoRun;
	CodeRunner->MaxStepsPerFrame = MaxSteps;

	CurrentState = EInterpreterState::RunningCode;
	CodeRunner->RunCode(RootNode, symbolTable);
}

bool UInterpreter::IsCompileValid(FCompileData data)
{
	if (data.Errors.Messeges.Num() > 0) return false;
	if (data.Tokens.Num() <= 0) return false;
	if (!data.AST) return false;
	if (!data.SymbolTable) return false;

	return true;
}

void UInterpreter::AbortCodeExecution()
{
	if (CurrentState != EInterpreterState::RunningCode) return;

	CodeRunner->AbortExecution();
	Clear();
}

void UInterpreter::AbortDueToRuntimeError(FString ErrorMessage)
{
	AbortCodeExecution();
	OnRuntimeError.Broadcast(ErrorMessage);
}


