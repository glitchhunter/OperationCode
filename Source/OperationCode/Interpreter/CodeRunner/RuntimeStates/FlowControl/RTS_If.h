// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/FlowControl/RTS_FlowControl.h"
#include "RTS_If.generated.h"

class UAST_If;

/**
 * 
 */
UCLASS()
class URTS_If : public URTS_FlowControl
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetIf(UAST_If* IfNode) { If = IfNode; }

protected:

	UPROPERTY()
	UAST_If* If;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool CheckedCondition;


	
	
	
};
