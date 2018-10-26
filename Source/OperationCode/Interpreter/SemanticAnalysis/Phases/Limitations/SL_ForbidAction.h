// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/SemanticAnalysis/Phases/Limitations/SemanticLimitation.h"
#include "SL_ForbidAction.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API USL_ForbidAction : public USemanticLimitation
{
	GENERATED_BODY()

public:

	virtual void StartAnalysis(UAST_Node* RootNode) override;

	bool RecursiveCheck(UAST_Node* node);



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		TSubclassOf<UAST_Node> ActionToForbid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ExposeOnSpawn = true))
		FString ErrorMessage;
	
	
	
	
};
