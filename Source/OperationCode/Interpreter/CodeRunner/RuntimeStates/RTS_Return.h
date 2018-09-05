// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/RuntimeState.h"
#include "RTS_Return.generated.h"

class UAST_Return;

/**
 * 
 */
UCLASS()
class URTS_Return : public URuntimeState
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetReturn(UAST_Return* ReturnNode) { Return = ReturnNode; }

protected:

	UPROPERTY()
	UAST_Return* Return;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool CheckedReturnExpression = false;
	
	
};
