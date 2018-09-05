// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/RuntimeState.h"
#include "ImplicitRTS.generated.h"

/**
 * Implicit runtime states have no AST node that they belong to. 
 * As name implies, they handle implied actions, such as initialization of classes,
 * or argument type conversions during function calls.
 */
UCLASS()
class UImplicitRTS : public URuntimeState
{
	GENERATED_BODY()
	
public:

	virtual UAST_Node* GetNode() const override { return nullptr; }
	
	
};
