// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/FlowControl/Loops/RTS_Loop.h"
#include "RTS_For.generated.h"

class UAST_For;

UENUM(BlueprintType)
enum class EForState : uint8
{
	Uninitialized,
	RunningInitialization,
	CheckingCondition,
	RunningLoopBody,
	RunningUpdate,
};

/**
 * 
 */
UCLASS()
class URTS_For : public URTS_Loop
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetFor(UAST_For* ForNode) { For = ForNode; }


protected:

	UPROPERTY()
	UAST_For* For;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EForState CurrentState = EForState::Uninitialized;



	
	
	
	
};
