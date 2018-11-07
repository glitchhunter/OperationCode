// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "CodeLevelScript.generated.h"

class ACodePlayerControllerBase;
class ULevelDataAsset;
class ULevelFlowAsset;

/**
 * 
 */
UCLASS(BlueprintType)
class OPERATIONCODE_API ACodeLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ManageLimitations();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ACodePlayerControllerBase* CodePC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ULevelDataAsset* LevelData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ULevelFlowAsset* LevelFlow;
	
	
};
