// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interpreter.generated.h"

class UCodeRunner;
class UToken;
class UAST_Node;
class USymbolTable;
class UAST_Basic;


UENUM(BlueprintType)
enum class EInterpreterState: uint8
{
	Idle,
	LexingCompleted,
	ParsingCompleted,
	AnalysisCompleted,
	RunningCode
};

USTRUCT(BlueprintType)
struct FInterpreterMessage
{
	GENERATED_BODY()

	FInterpreterMessage() {}

	FInterpreterMessage(TArray<FString> messeges, EInterpreterState phase)
	{
		Messeges = messeges;
		Phase = phase;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Messeges;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EInterpreterState Phase;
};

USTRUCT(BlueprintType)
struct FCompileData
{
	GENERATED_BODY()


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UToken*> Tokens;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAST_Node* AST;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USymbolTable* SymbolTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInterpreterMessage Errors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FString> Warnings;

};

/**
 * 
 */
UCLASS(Blueprintable)
class OPERATIONCODE_API UInterpreter : public UObject
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOutputDelegate, FString, Message);
	
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCodeCompleted);

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FStaticInitializationCompleted);

public:

	virtual UWorld* GetWorld() const override;

	UFUNCTION(BlueprintCallable)
	void Clear();

	UFUNCTION(BlueprintCallable)
	FCompileData Compile(FString SourceCode, UAST_Basic* Root, UValue* TopOwner);

	UFUNCTION(BlueprintCallable)
	TArray<UToken*> Lex(FString SourceCode);

	UFUNCTION(BlueprintCallable)
	TArray<UAST_Node*> Parse(TArray<UToken*> Tokens);

	UFUNCTION(BlueprintCallable)
	USymbolTable* Analyse(UAST_Node* RootNode, UValue* TopOwner);

	UFUNCTION(BlueprintCallable)
	void RunCode(UAST_Node* RootNode, USymbolTable* symbolTable, bool AutoRun, int32 MaxSetps);

	UFUNCTION(BlueprintPure)
	TArray<FString> GetErrors() const { return Errors; }

	UFUNCTION(BlueprintPure)
	bool HasErrors() const { return Errors.Num() > 0; }

	UFUNCTION(BlueprintPure)
	static bool IsCompileValid(FCompileData data);

	UFUNCTION(BlueprintPure)
	EInterpreterState GetCurrentState() const { return CurrentState; }

	UFUNCTION(BlueprintPure)
	UCodeRunner* GetCodeRunner() const { return CodeRunner; }

	UFUNCTION(BlueprintCallable)
	void AbortCodeExecution();




	void SendMessage(FString Message) { OnRuntimeMessageSent.Broadcast(Message); }

	void SendLog(FString Log) { OnRuntimeLogSent.Broadcast(Log); }

	void StoreErrorMessage(FString Message) { Errors.Add(Message); }

	void CodeCompleted() { Clear(); OnCodeCompleted.Broadcast(); }

	UPROPERTY(BlueprintAssignable)
	FOutputDelegate OnRuntimeMessageSent;

	UPROPERTY(BlueprintAssignable)
	FOutputDelegate OnRuntimeLogSent;

	UPROPERTY(BlueprintAssignable)
	FCodeCompleted OnCodeCompleted;

	UPROPERTY(BlueprintAssignable)
	FStaticInitializationCompleted OnStaticInitCompleted;





protected:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCodeRunner* CodeRunner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EInterpreterState CurrentState;

	UPROPERTY(VisibleAnywhere)
	TArray<FString> Errors;

	UPROPERTY(VisibleAnywhere)
	TArray<FString> Warnings;
	
	
	
	
};
