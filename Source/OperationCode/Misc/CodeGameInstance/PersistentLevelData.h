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

UCLASS(Blueprintable)
class OPERATIONCODE_API UPersistentLevelData : public UObject
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 PuzzleIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 HintIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSet<UTeachableDataAsset*> ExtraTeachables;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FNotificationData> Notifications;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FDateTime LevelStartTime;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 UserRequestedHintsCount;

};
