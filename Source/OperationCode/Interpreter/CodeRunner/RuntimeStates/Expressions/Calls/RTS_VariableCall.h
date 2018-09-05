// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Calls/RTS_Call.h"
#include "RTS_VariableCall.generated.h"

class UAST_VariableCall;

/**
 * 
 */
UCLASS()
class URTS_VariableCall : public URTS_Call
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetVariableCall(UAST_VariableCall* variableCall) { VariableCall = variableCall; }

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UValue* Owner;

private:

	UPROPERTY()
	UAST_VariableCall* VariableCall;

	
	
	
	
};
