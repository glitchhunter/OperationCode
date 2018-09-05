// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Operators/RTS_Operator.h"
#include "RTS_TwoArguments.generated.h"

class UAST_TwoArguments;

/**
 * 
 */
UCLASS()
class URTS_TwoArguments : public URTS_Operator
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetTwoArguments(UAST_TwoArguments* twoArguments) { TwoArguments = twoArguments; }

protected:

	UPROPERTY()
	UAST_TwoArguments* TwoArguments;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ArgumentsManaged;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UValue* lhsVal;
	
	
	
	
};
