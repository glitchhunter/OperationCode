// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "CodeLevelScript.generated.h"

class ACodePlayerControllerBase;
class USemanticLimitation;
class UAST_ClassDefinition;
class UAST_FunctionDefinition;

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API ACodeLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintPure, BlueprintNativeEvent)
	FString GetLevelText() const;



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	TArray<USemanticLimitation*> Limitations;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ACodePlayerControllerBase* CodePC;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UAST_ClassDefinition>> PredefinedClasses;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TSubclassOf<UAST_FunctionDefinition>> PredefinedFunctions;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (MultiLine = "true"))
	FString LevelText;
	
	
};
