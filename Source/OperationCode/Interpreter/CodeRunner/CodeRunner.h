// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/InterpreterComponent.h"
#include "StackFrame.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "CodeRunner.generated.h"

class UAST_Node;
class USymbolTable;
class UValue;
class UTypeValue;
class UBoolInstance;
class UIntInstance;
class UFloatInstance;
class UStringInstance;
class UAST_FunctionDefinition;


UENUM(BlueprintType)
enum class ECodeState : uint8
{
	NotRunning,
	WaitingForNextStep,
	Running
};

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UCodeRunner : public UInterpreterComponent
{
	GENERATED_BODY()
	
public:

	bool HasStackFrame() const;

	FStackFrame GetStackFrame() const;

	bool HasRTS() const;

	URuntimeState* GetRTS() const;

	bool HasScope() const;

	FScope GetScope() const;

	void SetValue(UValue* Value);

	UValue* GetValue() const;





	void AddScope();

	void PopScope();

	void AddStackFrame(UValue* StackOwner);

	void PopStackFrame();

	void AddVariable(FString Varname, UValue* Value);

	void AddRTS(URuntimeState* RuntimeState);

	void PopRTS();

	UFUNCTION(BlueprintCallable)
	UValue* GetVariable(FString VarName);

	UFUNCTION(BlueprintCallable)
	void RunNextRTSStep();

	void RTSStepCompleted();

	void CodeCompleted();

	UFUNCTION(BlueprintCallable)
	void RunCode(UAST_Node* RootNode, USymbolTable* symbolTable);

	UTypeValue* GetTypeValue(FString Type);

	void AddTypeValue(UTypeValue* NewTypeValue);

	UFUNCTION(BlueprintCallable)
	void AddDebugMessage(FString Message) { GetInterpreter()->SendLog(Message); }

	UFUNCTION(BlueprintCallable)
	void AddOutputMessage(FString Message) { GetInterpreter()->SendMessage(Message); }

	void SetTempOwner(UValue* temp) { TempOwner = temp; }

	UValue* ConsumeTempOwner()
	{
		UValue* temp = TempOwner;
		TempOwner = nullptr;
		return temp;
	}

	UFUNCTION()
		void FrameDelay();


	UValue* GetOwner() const;


	void AbortExecution();


	USymbolTable* GetSymbolTable() const { return SymbolTable; }

	TArray<FStackFrame> GetStack() const { return Stack; }








	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool AutoRun = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 MaxStepsPerFrame = 500;


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool Aborting;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USymbolTable* SymbolTable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FStackFrame> Stack;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ECodeState CurrentCodeState;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FString, UTypeValue*> TypeValues;

	UPROPERTY(VisibleAnywhere, blueprintReadWrite)
	UValue* ReturnedValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 StepCounter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UValue* TempOwner;

	FTimerHandle FrameDelayTimerHandle;
	
};
