// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeLevelScript.h" 
#include "Kismet/GameplayStatics.h"
#include "Misc/CodePlayerControllerBase.h"
#include "Interpreter/Parser/AST/Definition/AST_ClassDefinition.h"
#include "Interpreter/Parser/AST/Definition/AST_FunctionDefinition.h"
#include "Misc/LevelDataAsset.h"
#include "Misc/LevelFlowAsset.h"
#include "CodeGameInstance/CodeGameInstanceBase.h"


ACodeLevelScript::ACodeLevelScript(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PldClass = UPersistentLevelData::StaticClass();
	AutoSaveOnNewLevelStart = true;
	LevelCompletedHint = "You're done. Just leave.";
}


void ACodeLevelScript::BeginPlay()
{
	CodeGameInstance = Cast<UCodeGameInstanceBase>(GetGameInstance());
	if (CodeGameInstance)
	{
		// No stored data, or data that came from another level, mean that this level loaded for the first time.
		if (!CodeGameInstance->GetPLD() || CodeGameInstance->GetPLD()->LevelName != GetWorld()->GetMapName())
		{
			FirstLoadSetup(CodeGameInstance);
		}
		else
		{
			OnLoad(CodeGameInstance->GetPLD());
		}

		// Bind on puzzle index changed
		CodeGameInstance->GetPLD()->OnNewPuzzleIndex.AddDynamic(this, &ACodeLevelScript::NewPuzzleStarted);
	}

	APlayerController* cont = UGameplayStatics::GetPlayerController(this, 0);
	CodePC = Cast<ACodePlayerControllerBase>(cont);
	CodePC->LevelScript = this;
	ManageLimitations();

	if (LevelData)
	{
		for (TSubclassOf<UAST_ClassDefinition> current : LevelData->PredefinedClasses)
		{
			CodePC->AddClass(NewObject<UAST_ClassDefinition>(CodePC, current));
		}

		for (TSubclassOf<UAST_FunctionDefinition> current : LevelData->PredefinedFunctions)
		{
			CodePC->ExtraFunctions.Add(NewObject<UAST_FunctionDefinition>(CodePC, current));
		}
	}

	Super::BeginPlay();
}

void ACodeLevelScript::ManageLimitations_Implementation()
{
	if (!LevelData || !LevelFlow) return;

	// First add level specific limitations
	CodePC->GetInterpreter()->Limitations.Append(LevelData->LevelSpecificLimitations);

	// Iterate through all chapters from end
	for (int i = LevelFlow->Chapters.Num() - 1; i >= 0; --i)
	{
		// Iterate through all levels from end
		for (int j = LevelFlow->Chapters[i].Levels.Num() - 1; j >= 0; --j)
		{
			ULevelDataAsset* currentLevel = LevelFlow->Chapters[i].Levels[j];
			if (!currentLevel) continue;

			// If we reached this level, stop. Earlier limitations are removed.
			if (currentLevel == LevelData) return;

			// Append limitation
			CodePC->GetInterpreter()->Limitations.Append(currentLevel->Unlocks);
		}
	}
}


UPersistentLevelData* ACodeLevelScript::GetPLD() const
{
	return CodeGameInstance->GetPLD();
}

void ACodeLevelScript::FirstLoadSetup(UCodeGameInstanceBase* CodeGameInstance)
{
	IsFirstLoad = true;
	if (PldClass) CodeGameInstance->CreatePLD(PldClass);
	else
	{
		// Backup in case the class is null
		CodeGameInstance->CreatePLD(UPersistentLevelData::StaticClass());
	}
	
	CodeGameInstance->GetPLD()->LevelName = GetWorld()->GetMapName();
	CodeGameInstance->GetPLD()->LevelStartTime = FDateTime::Now();
}


void ACodeLevelScript::SetPuzzleIndex(const int32 NewIndex, bool HigherOnly /* = true */)
{
	if (!CodeGameInstance || !CodeGameInstance->GetPLD())
	{
		UE_LOG(LogTemp, Error, TEXT("Trying to set puzzle index to %i, but level didn't initialize yet."), NewIndex);
		return;
	}
	CodeGameInstance->GetPLD()->SetPuzzleIndex(NewIndex, HigherOnly);
}

bool ACodeLevelScript::GetNextHintText_Implementation(FString& HintText)
{
	if (!HintData.IsValidIndex(GetPLD()->GetPuzzleIndex()) || IsLevelSolved())
	{
		HintText = LevelCompletedHint;
		return false;
	}
	if (!HintData[GetPLD()->GetPuzzleIndex()].HintText.IsValidIndex(GetPLD()->HintIndex))
	{
		HintText = HintData[GetPLD()->GetPuzzleIndex()].NoMoreHintsText;
		return false;
	}
	HintText = HintData[GetPLD()->GetPuzzleIndex()].HintText[GetPLD()->HintIndex];
	GetPLD()->HintIndex++;
	GetPLD()->UserRequestedHintsCount++;
	return true;
}

void ACodeLevelScript::OnLoad_Implementation(UPersistentLevelData* PLD)
{
	IsFirstLoad = false;
	PLD->ReloadCount++;
}

bool ACodeLevelScript::IsPuzzleCompleted(int32 index)
{
	return GetPLD()->GetPuzzleIndex() > index;
}

bool ACodeLevelScript::CompleteThisPuzzle()
{
	if (!CodeGameInstance || !CodeGameInstance->GetPLD()) return false;
	return CompletePuzzle(CodeGameInstance->GetPLD()->GetPuzzleIndex());
}

bool ACodeLevelScript::CompletePuzzle(int32 index)
{
	if (!CodeGameInstance || !CodeGameInstance->GetPLD()) return false;
	if (IsLevelSolved()) return false;
	
	SetPuzzleIndex(index + 1);
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()));
	return true;
}

