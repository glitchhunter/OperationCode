// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/SemanticAnalysis/Phases/Limitations/SemanticLimitation.h"
#include "BlueprintSemanticLimitation.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class OPERATIONCODE_API UBlueprintSemanticLimitation : public USemanticLimitation
{
	GENERATED_BODY()

public:

	virtual void StartAnalysis(UAST_Node* RootNode) override;

	UFUNCTION(BlueprintImplementableEvent)
		bool IsCheckValid(UAST_Node* RootNode);

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
		FString GetErrorMessage() const;
	
	
};
