// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/FlowControl/Loops/RTS_Loop.h"
#include "RTS_DoWhile.generated.h"

class UAST_DoWhile;

/**
 * 
 */
UCLASS()
class URTS_DoWhile : public URTS_Loop
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetDoWhile(UAST_DoWhile* DoWhileNode) { DoWhile = DoWhileNode; }

protected:

	UPROPERTY()
	UAST_DoWhile* DoWhile;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool CheckedCondition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool HasAddedScope;

	
	
	
	
};
