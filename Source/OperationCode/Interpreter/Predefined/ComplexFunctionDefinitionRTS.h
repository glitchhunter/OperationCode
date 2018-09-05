// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/Definitions/RTS_FunctionDefinition.h"
#include "ComplexFunctionDefinitionRTS.generated.h"

class UComplexPredefinedFunction;

/**
 * 
 */
UCLASS(Blueprintable)
class OPERATIONCODE_API UComplexFunctionDefinitionRTS : public URTS_FunctionDefinition
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetComplexFunctionDefinition(UComplexPredefinedFunction* complexFunctionDefinition) { ComplexFunctionDefinition = complexFunctionDefinition; }

	UFUNCTION(BlueprintImplementableEvent, meta = (DsiplayName = "Run step"))
	void RunStep_BP();

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Step completed"))
	void StepCompleted_BP() { StepCompleted(); }

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Finished"))
	void Finished_BP(UValue* returnValue);

protected:

	UPROPERTY()
		UComplexPredefinedFunction* ComplexFunctionDefinition;

	
};
