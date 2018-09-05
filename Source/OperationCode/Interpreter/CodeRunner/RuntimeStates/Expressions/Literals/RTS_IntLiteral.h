// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Literals/RTS_Literal.h"
#include "RTS_IntLiteral.generated.h"

class UAST_IntLiteral;

/**
 * 
 */
UCLASS()
class URTS_IntLiteral : public URTS_Literal
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetIntLiteral(UAST_IntLiteral* intLiteral) { IntLiteral = intLiteral; }

private:

	UPROPERTY()
		UAST_IntLiteral* IntLiteral;
	
	
	
	
};
