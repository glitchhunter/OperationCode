// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeGameInstanceBase.h"
#include "PersistentLevelData.h"


UPersistentLevelData* UCodeGameInstanceBase::CreatePLD(TSubclassOf<UPersistentLevelData> Class)
{
	if (!Class) return nullptr;
	PLD = NewObject<UPersistentLevelData>(this, Class);
	return PLD;
}

