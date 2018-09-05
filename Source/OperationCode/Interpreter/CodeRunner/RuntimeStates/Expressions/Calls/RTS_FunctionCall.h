// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Calls/RTS_Call.h"
#include "RTS_FunctionCall.generated.h"

class UAST_FunctionCall;
class UAST_FunctionDefinition;

/**
 * 
 */
UCLASS()
class URTS_FunctionCall : public URTS_Call
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetFunctionCall(UAST_FunctionCall* functionCall) { FunctionCall = functionCall; }

protected:

	UAST_FunctionDefinition* GetFunctionDefinition();

	UPROPERTY()
	UAST_FunctionCall* FunctionCall;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ParamIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UValue* value;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UValue*> Parameters;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAST_FunctionDefinition* Definition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UValue* owner;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool OwnerSet;
	
};
