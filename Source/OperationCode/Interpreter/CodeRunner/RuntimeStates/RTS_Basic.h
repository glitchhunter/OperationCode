// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/RuntimeState.h"
#include "RTS_Basic.generated.h"

class UAST_Basic;

/**
 * 
 */
UCLASS()
class URTS_Basic : public URuntimeState
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetBasic(UAST_Basic* basic) { Basic = basic; }

protected:

	UPROPERTY()
	UAST_Basic* Basic;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentChildIndex = 0;


	
	
	
	
};
