// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Misc/Notifications/NotificationData.h"
#include "Runtime/Core/Public/Misc/DateTime.h"
#include "PersistentLevelData.generated.h"

/**
 * 
 */

class UTeachableDataAsset;



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FNewPuzzle, int32, NewPuzzleIndex);

UCLASS(Blueprintable)
class OPERATIONCODE_API UPersistentLevelData : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString LevelName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 HintIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CheckpointIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 FailedCompilesCount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 ReloadCount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSet<UTeachableDataAsset*> ExtraTeachables;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FNotificationData> Notifications;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FDateTime LevelStartTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 UserRequestedHintsCount;

	UPROPERTY(BlueprintAssignable)
	FNewPuzzle OnNewPuzzleIndex;



	UFUNCTION(BlueprintCallable)
	void SetPuzzleIndex(int32 NewPuzzleIndex, bool HigherOnly = true);
	
	UFUNCTION(BlueprintPure)
	int32 GetPuzzleIndex() const { return PuzzleIndex; }



protected:

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	int32 PuzzleIndex;

};
