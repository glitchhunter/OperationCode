// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "LevelDataAsset.generated.h"

class USemanticLimitation;
class UTeachableDataAsset;
class UAST_ClassDefinition;
class UAST_FunctionDefinition;


/**
 * 
 */
UCLASS(Blueprintable)
class OPERATIONCODE_API ULevelDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString LevelName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UAST_ClassDefinition>> PredefinedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UAST_FunctionDefinition>> PredefinedFunctions;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<USemanticLimitation*> Unlocks;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced)
	TArray<USemanticLimitation*> LevelSpecificLimitations;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UTeachableDataAsset*> TeachableData;

};
