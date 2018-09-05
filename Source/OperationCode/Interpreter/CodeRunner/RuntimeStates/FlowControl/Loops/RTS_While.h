// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/FlowControl/Loops/RTS_Loop.h"
#include "RTS_While.generated.h"

class UAST_While;

/**
 * 
 */
UCLASS()
class URTS_While : public URTS_Loop
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetWhile(UAST_While* WhileNode) { While = WhileNode; }

protected:

	UPROPERTY()
	UAST_While* While;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool CheckedCondition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool HasAddedScope;
	
	
};
