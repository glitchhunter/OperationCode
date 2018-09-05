// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Literals/RTS_Literal.h"
#include "RTS_NullptrLiteral.generated.h"

class UAST_NullptrLiteral;

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API URTS_NullptrLiteral : public URTS_Literal
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetNullptrLiteral(UAST_NullptrLiteral* NullptrLiteral) { Nullptr = NullptrLiteral; }

private:

	UPROPERTY()
	UAST_NullptrLiteral* Nullptr;
	
	
	
	
};
