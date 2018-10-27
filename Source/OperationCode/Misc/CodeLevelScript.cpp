// Fill out your copyright notice in the Description page of Project Settings.

#include "CodeLevelScript.h" 
#include "Kismet/GameplayStatics.h"
#include "Misc/CodePlayerControllerBase.h"
#include "Interpreter/Parser/AST/Definition/AST_ClassDefinition.h"
#include "Interpreter/Parser/AST/Definition/AST_FunctionDefinition.h"


void ACodeLevelScript::BeginPlay()
{
	APlayerController* cont = UGameplayStatics::GetPlayerController(this, 0);
	CodePC = Cast<ACodePlayerControllerBase>(cont);

	CodePC->Limitations = Limitations;
	
	for (TSubclassOf<UAST_ClassDefinition> current : PredefinedClasses)
	{
		CodePC->AddClass(NewObject<UAST_ClassDefinition>(CodePC, current));
	}

	for (TSubclassOf<UAST_FunctionDefinition> current : PredefinedFunctions)
	{
		CodePC->ExtraFunctions.Add(NewObject<UAST_FunctionDefinition>(CodePC, current));
	}

	Super::BeginPlay();
}

