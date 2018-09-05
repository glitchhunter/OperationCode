// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Operators/RTS_Operator.h"
#include "RTS_OneArgument.generated.h"

class UAST_OneArgument;

/**
 * 
 */
UCLASS()
class URTS_OneArgument : public URTS_Operator
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetOneArgument(UAST_OneArgument* oneArgument) { OneArgument = oneArgument; }
	
protected:

	UPROPERTY()
		UAST_OneArgument* OneArgument;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool ArgumentManaged;
	
	
};
