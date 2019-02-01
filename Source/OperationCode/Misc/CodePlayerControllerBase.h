// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interpreter/Interpreter.h"
#include "Interpreter/FunctionData.h"
#include "CodePlayerControllerBase.generated.h"

class USemanticLimitation;
class UInterpreter;
class UValue;
class UAST_Basic;
class UAST_ClassDefinition;
class UAST_FunctionDefinition;
struct FCompileData;
struct FFunctionSignature;

class ACodeLevelScript;

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API ACodePlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
public:

	ACodePlayerControllerBase();

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Code")
		bool Compile(const FString& SourceCode);

	UFUNCTION(BlueprintPure, Category = "Code")
		bool CanCompile();

	UFUNCTION(BlueprintCallable, Category = "Code")
		void RunCode(bool AutoRun);

	UFUNCTION(BlueprintPure, Category = "Code")
		bool CanRunCode();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Code")
		void Clear();

	UFUNCTION(BlueprintCallable, Category = "Code")
		void SetMaxSteps(int32 NewMaxSteps);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Code")
		UAST_Basic* GetPrecompiledData();

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "Code")
		UValue* GetTopOwner();

	UFUNCTION(BlueprintCallable, Category = "Code")
		void ClearCompileData() { CompileData = FCompileData(); }


	UFUNCTION(BlueprintImplementableEvent, Category = "Code")
		void OnRuntimeMessageSent(const FString& Message);

	UFUNCTION(BlueprintImplementableEvent, Category = "Code")
		void OnRuntimeLogSent(const FString& Message);

	UFUNCTION(BlueprintImplementableEvent, Category = "Code")
		void OnStaticinitCompleted();

	UFUNCTION(BlueprintImplementableEvent, Category = "Code")
		void OnCodeCompleted();

	UFUNCTION(BlueprintImplementableEvent, Category = "Code")
		void OnRuntimeError(const FString& Message);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Code")
		void AddClass(UAST_ClassDefinition* ClassDefinition);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Code")
		void RemoveClass(const FString& ClassName);

	UFUNCTION(BlueprintPure, Category = "Code")
		bool IsClassAlreadyDefined(const FString& ClassName);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Code")
		void AddFunction(UAST_FunctionDefinition* FunctionDefinition);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Code")
		void RemoveFunction(const FFunctionSignature& FunctionSig);

	UFUNCTION(BlueprintPure)
		UInterpreter* GetInterpreter() const { return Interp; }







	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FCompileData CompileData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int32 MaxSteps = 500;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UAST_ClassDefinition*> ExtraClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<UAST_FunctionDefinition*> ExtraFunctions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UAST_Basic> BasicType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TMap<FString, int32> ClassCounter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		TMap<FFunctionSignature, int32> FunctionCounter;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		ACodeLevelScript* LevelScript;


private:

	UPROPERTY(VisibleAnywhere, Export)
		UInterpreter* Interp;
	
	
};
