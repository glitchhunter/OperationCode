// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "CodeGameInstance/PersistentLevelData.h"
#include "Misc/PuzzleHintData.h"
#include "Runtime/Core/Public/Misc/DateTime.h"
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

	UFUNCTION(BlueprintCallable)
	void SetPuzzleIndex(const int32 NewIndex, bool HigherOnly = true);

	UFUNCTION(BlueprintCallable)
	bool GetNextHintText(FString& HintText);

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void NewPuzzleStarted(int32 index);

	UFUNCTION(BlueprintNativeEvent)
	void OnLoad(UPersistentLevelData* PLD);

	UFUNCTION(BlueprintPure)
	bool GetIsFirstLoad() { return IsFirstLoad; }

	UFUNCTION(BlueprintPure)
	UPersistentLevelData* GetPLD() const;

	UFUNCTION(BlueprintPure)
	bool IsPuzzleCompleted(int32 index);

	UFUNCTION()
	void FirstLoadSetup(UCodeGameInstanceBase* CodeGameInstance);




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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool AutoSaveOnNewLevelStart;

private:

	UPROPERTY()
	bool IsFirstLoad;
	
	
};
