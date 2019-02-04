// Fill out your copyright notice in the Description page of Project Settings.

#include "PersistentLevelData.h"



void UPersistentLevelData::SetPuzzleIndex(int32 NewPuzzleIndex, bool HigherOnly /* = true */)
{
	if (HigherOnly && NewPuzzleIndex <= PuzzleIndex) return;

	PuzzleIndex = NewPuzzleIndex;
	HintIndex = 0;
	OnNewPuzzleIndex.Broadcast(PuzzleIndex);
}