// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/FlowControl/AST_FlowControl.h"
#include "AST_Loop.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class OPERATIONCODE_API UAST_Loop : public UAST_FlowControl
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	UAST_Node* Body;
	
	
};
