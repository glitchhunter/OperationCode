// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/Definitions/RTS_Definition.h"
#include "RTS_FunctionDefinition.generated.h"

class UAST_FunctionDefinition;

/**
 * 
 */
UCLASS()
class URTS_FunctionDefinition : public URTS_Definition
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetFunctionDefinition(UAST_FunctionDefinition* functionDefinition) { FunctionDefinition = functionDefinition; }





	UFUNCTION(BlueprintCallable)
		UValue* GetVariable(FString VarName);

	UFUNCTION(BlueprintCallable)
		UBoolInstance* GetBoolVariable(FString VarName);

	UFUNCTION(BlueprintCallable)
		bool GetBoolValue(FString VarName);

	UFUNCTION(BlueprintCallable)
		UIntInstance* GetIntVariable(FString VarName);

	UFUNCTION(BlueprintCallable)
		int32 GetIntValue(FString VarName);

	UFUNCTION(BlueprintCallable)
		UFloatInstance* GetFloatVariable(FString VarName);

	UFUNCTION(BlueprintCallable)
		float GetFloatValue(FString VarName);

	UFUNCTION(BlueprintCallable)
		UStringInstance* GetStringVariable(FString VarName);

	UFUNCTION(BlueprintCallable)
		FString GetStringValue(FString VarName);

	UFUNCTION(BlueprintCallable)
		UValue* GetOwner();



protected:

	UPROPERTY()
	UAST_FunctionDefinition* FunctionDefinition;

	UPROPERTY()
	bool ScopeCompleted;
	
};
