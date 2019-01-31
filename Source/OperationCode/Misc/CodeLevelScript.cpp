// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeLevelScript.h" 
#include "Kismet/GameplayStatics.h"
#include "Misc/CodePlayerControllerBase.h"
#include "Interpreter/Parser/AST/Definition/AST_ClassDefinition.h"
#include "Interpreter/Parser/AST/Definition/AST_FunctionDefinition.h"
#include "Misc/LevelDataAsset.h"
#include "Misc/LevelFlowAsset.h"
#include "CodeGameInstance/CodeGameInstanceBase.h"


ACodeLevelScript::ACodeLevelScript(const FObjectInitializer& ObjectInitializer)
{
	PldClass = UPersistentLevelData::StaticClass();
}


void ACodeLevelScript::BeginPlay()
{
	CodeGameInstance = Cast<UCodeGameInstanceBase>(GetGameInstance());
	if (CodeGameInstance)
	{
		CodeGameInstance->OnSave.AddDynamic(this, &ACodeLevelScript::OnSave);

		// No PLD means that this level has no data to load, so we create one.
		if (!CodeGameInstance->GetPLD())
		{
			if (PldClass) CodeGameInstance->CreatePLD(PldClass);
			else
			{
				// Backup in case the class is null
				CodeGameInstance->CreatePLD(UPersistentLevelData::StaticClass());
			}
		}
		else
		{
			// PLD exists, so we the level reloaded.
			PuzzleIndex = CodeGameInstance->GetPLD()->PuzzleIndex;
			HintIndex = CodeGameInstance->GetPLD()->HintIndex;
		}
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
	CodePC->Interpreter->Limitations.Append(LevelData->LevelSpecificLimitations);

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
			CodePC->Interpreter->Limitations.Append(currentLevel->Unlocks);
		}
	}
}


int32 ACodeLevelScript::GetPuzzleIndex_Implementation() const
{
	return PuzzleIndex;
}

void ACodeLevelScript::SetPuzzleIndex(const int32 NewIndex, bool HigherOnly /* = true */)
{
	if (HigherOnly && NewIndex <= GetPuzzleIndex()) return;

	PuzzleIndex = NewIndex;
	HintIndex = 0;
}

bool ACodeLevelScript::GetNextHintText(FString& HintText)
{
	if (!HintData.IsValidIndex(GetPuzzleIndex())) return false;
	if (!HintData[GetPuzzleIndex()].HintText.IsValidIndex(GetHintIndex())) return false;
	HintText = HintData[GetPuzzleIndex()].HintText[GetHintIndex()];
	HintIndex++;
	return true;
}

void ACodeLevelScript::OnSave_Implementation(UPersistentLevelData* PLD)
{
	PLD->PuzzleIndex = GetPuzzleIndex();
	PLD->HintIndex = HintIndex;
}

