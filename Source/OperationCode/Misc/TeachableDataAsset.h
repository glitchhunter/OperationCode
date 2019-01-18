// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TeachableDataAsset.generated.h"

class UUserWidget;
class UTeachableSegment;

UENUM(BlueprintType)
enum class ETeachableType : uint8
{
	Concept,
	Tutorial
};

UCLASS(Blueprintable, EditInlineNew)
class OPERATIONCODE_API UTeachableSegment : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	UUserWidget* GetWidget(UObject* WorldContext);

	UFUNCTION(BlueprintCallable)
	UUserWidget* CreateTeachableWidget(TSubclassOf<UUserWidget> WidgetClass, UObject* WorldContext);
};


/**
 * 
 */
UCLASS(Blueprintable)
class OPERATIONCODE_API UTeachableDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Title;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	TArray<UTeachableSegment*> Segments;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETeachableType Type;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<UTeachableDataAsset*> RelatedTeachables;
	
};
