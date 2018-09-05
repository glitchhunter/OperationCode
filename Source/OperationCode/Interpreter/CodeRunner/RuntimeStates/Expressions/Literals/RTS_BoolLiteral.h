// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Literals/RTS_Literal.h"
#include "RTS_BoolLiteral.generated.h"

class UAST_BoolLiteral;

/**
 * 
 */
UCLASS()
class URTS_BoolLiteral : public URTS_Literal
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetBoolLiteral(UAST_BoolLiteral* boolLiteral) { BoolLiteral = boolLiteral; }

private:

	UPROPERTY()
		UAST_BoolLiteral* BoolLiteral;
	
	
	
};
