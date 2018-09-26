// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/Definitions/RTS_FunctionDefinition.h"
#include "SimpleFunctionDefinitionRTS.generated.h"

class USimplePredefinedFunction;

/**
 * 
 */
UCLASS()
class USimpleFunctionDefinitionRTS : public URTS_FunctionDefinition
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetPredefinedFunctionDefinition(USimplePredefinedFunction* simpleFunction);


protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	USimplePredefinedFunction* SimpleFunction;

	
	
	
};
