// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "CodeGameInstance/PersistentLevelData.h"
#include "Misc/PuzzleHintData.h"
#include "CodeLevelScript.generated.h"

class ACodePlayerControllerBase;
class ULevelDataAsset;
class ULevelFlowAsset;
class UCodeGameInstanceBase;
class UPersistentLevelData;

/**
 * 
 */
UCLASS(BlueprintType)
class OPERATIONCODE_API ACodeLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:

	ACodeLevelScript(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ManageLimitations();

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	int32 GetPuzzleIndex() const;

	UFUNCTION(BlueprintCallable)
	void SetPuzzleIndex(const int32 NewIndex, bool HigherOnly = true);

	UFUNCTION(BlueprintPure)
	int32 GetHintIndex() const { return HintIndex; }

	UFUNCTION(BlueprintCallable)
	bool GetNextHintText(FString& HintText);

	UFUNCTION(BlueprintNativeEvent)
	void OnSave(UPersistentLevelData* PLD);




	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ACodePlayerControllerBase* CodePC;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ULevelDataAsset* LevelData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ULevelFlowAsset* LevelFlow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UPersistentLevelData> PldClass = UPersistentLevelData::StaticClass();;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UCodeGameInstanceBase* CodeGameInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FPuzzleHintData> HintData;



protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 HintIndex;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 PuzzleIndex;
	
	
};
