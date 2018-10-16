// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interpreter/CodeRunner/CodeRunner.h"
#include "RuntimeState.generated.h"

class UAST_Node;

/**
 * 
 */
UCLASS(BlueprintType)
class URuntimeState : public UObject
{
	GENERATED_BODY()

public:

	virtual UWorld* GetWorld() const override;

	virtual UAST_Node* GetNode() const PURE_VIRTUAL(URuntimeState::GetNode, { return nullptr; })

	void Init(UCodeRunner* codeRunnner) { CodeRunner = codeRunnner; }

	UFUNCTION(BlueprintPure)
	UCodeRunner* GetCodeRunner() const { return CodeRunner; }

	virtual void RunStep() PURE_VIRTUAL(URuntimeState::RunStep, );

	void StepCompleted();

	void Finished();

	void AddRTSToCodeRunner(UAST_Node* Node);

	void AddScope();

	bool GetIsCompleted() const { return IsCompleted; }

	bool HasAddedScope() const { return AddedScope; }

	UFUNCTION(BlueprintCallable)
	void AddDebugMessage(FString Message);

	UFUNCTION(BlueprintCallable)
	void ThrowRuntimeError(FString ErrorMessage);

private:

	UPROPERTY()
	UCodeRunner* CodeRunner;

	bool AddedScope = false;

	bool IsCompleted;

	
	
};
