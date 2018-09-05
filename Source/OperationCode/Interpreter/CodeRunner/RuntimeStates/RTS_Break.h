// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/RuntimeState.h"
#include "RTS_Break.generated.h"

class UAST_Break;

/**
 * 
 */
UCLASS()
class URTS_Break : public URuntimeState
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetBreak(UAST_Break* BreakNode) { Break = BreakNode; }

private:

	UPROPERTY()
	UAST_Break* Break;
	
	
	
};
