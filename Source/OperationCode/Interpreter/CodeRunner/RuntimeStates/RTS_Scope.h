// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/RuntimeState.h"
#include "RTS_Scope.generated.h"

class UAST_Scope;

/**
 * 
 */
UCLASS()
class URTS_Scope : public URuntimeState
{
	GENERATED_BODY()
	
public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetScope(UAST_Scope* scope) { Scope = scope; }

protected:

	UPROPERTY()
	UAST_Scope* Scope;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 CurrentChildIndex = 0;
	
};
