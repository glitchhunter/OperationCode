// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "CodeGameInstanceBase.generated.h"

/**
 * 
 */

class UPersistentLevelData;


UCLASS()
class OPERATIONCODE_API UCodeGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()
	
	
public:

	UFUNCTION(BlueprintCallable)
		UPersistentLevelData* CreatePLD(TSubclassOf<UPersistentLevelData> Class);

	UFUNCTION(BlueprintPure)
	UPersistentLevelData* GetPLD() const { return PLD; }

	UFUNCTION(BlueprintCallable)
	void ClearPLD() { PLD = nullptr; }

private:

	UPROPERTY()
	UPersistentLevelData* PLD;
		
};
