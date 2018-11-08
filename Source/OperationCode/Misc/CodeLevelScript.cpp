// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeLevelScript.h" 
#include "Kismet/GameplayStatics.h"
#include "Misc/CodePlayerControllerBase.h"
#include "Interpreter/Parser/AST/Definition/AST_ClassDefinition.h"
#include "Interpreter/Parser/AST/Definition/AST_FunctionDefinition.h"
#include "Misc/LevelDataAsset.h"
#include "Misc/LevelFlowAsset.h"


void ACodeLevelScript::BeginPlay()
{
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
			CodePC->Interpreter->Limitations.Append(currentLevel->Limitations);
		}
	}
}


