// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/Definitions/RTS_Definition.h"
#include "RTS_VariableDefinition.generated.h"

class UAST_VariableDefinition;

/**
 * 
 */
UCLASS()
class URTS_VariableDefinition : public URTS_Definition
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetVariableDefinition(UAST_VariableDefinition* variableDefinition) { VariableDefinition = variableDefinition; }

protected:

	UPROPERTY()
	UAST_VariableDefinition* VariableDefinition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool ExpressionManaged;

	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	bool VariableCreated = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool TypeConverted;
	
	
	
};
