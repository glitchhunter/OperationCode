// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/RTS_Expression.h"
#include "RTS_Type.generated.h"

class UAST_Type;

/**
 * 
 */
UCLASS()
class URTS_Type : public URTS_Expression
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetType(UAST_Type* type) { Type = type; }

private:

	UPROPERTY()
	UAST_Type* Type;
	
	
	
	
};
