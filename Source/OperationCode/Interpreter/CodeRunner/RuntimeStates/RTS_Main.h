// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/RuntimeState.h"
#include "RTS_Main.generated.h"

class UAST_Main;

/**
 * 
 */
UCLASS()
class URTS_Main : public URuntimeState
{
	GENERATED_BODY()
	
public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetMain(UAST_Main* main) { Main = main; }

protected:

	UPROPERTY()
	UAST_Main* Main;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentChildIndex = 0;
	
	
	
};
