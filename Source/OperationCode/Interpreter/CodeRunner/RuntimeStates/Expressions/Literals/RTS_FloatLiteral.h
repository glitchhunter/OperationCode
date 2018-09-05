// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Literals/RTS_Literal.h"
#include "RTS_FloatLiteral.generated.h"

class UAST_FloatLiteral;

/**
 * 
 */
UCLASS()
class URTS_FloatLiteral : public URTS_Literal
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetFloatLiteral(UAST_FloatLiteral* floatLiteral) { FloatLiteral = floatLiteral; }

private:

	UPROPERTY()
		UAST_FloatLiteral* FloatLiteral;


	
	
	
	
};
