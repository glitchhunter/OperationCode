// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/RuntimeState.h"
#include "RTS_Continue.generated.h"

class UAST_Continue;

/**
 * 
 */
UCLASS()
class URTS_Continue : public URuntimeState
{
	GENERATED_BODY()
	
public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetContinue(UAST_Continue* ContinueNode) { Continue = ContinueNode; }



private:

	UPROPERTY()
	UAST_Continue* Continue;

	
};
