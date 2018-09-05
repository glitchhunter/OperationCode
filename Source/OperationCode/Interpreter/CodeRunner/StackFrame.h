// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Values/Value.h"
#include "StackFrame.generated.h"

class URuntimeState;

/**
 * 
 */

USTRUCT(BlueprintType)
struct FScope
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, UValue*> ValuesInScope;

};

USTRUCT(BlueprintType)
struct FStackFrame
{
	GENERATED_BODY()
	
public:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<FScope> Scopes;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<URuntimeState*> RuntimeStates;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UValue* Owner;

	
};
