// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Literals/RTS_Literal.h"
#include "RTS_StringLiteral.generated.h"

class UAST_StringLiteral;

/**
 * 
 */
UCLASS()
class URTS_StringLiteral : public URTS_Literal
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetStringLiteral(UAST_StringLiteral* stringLiteral) { StringLiteral = stringLiteral; }

private:

	UPROPERTY()
		UAST_StringLiteral* StringLiteral;
	
	
	
	
};
