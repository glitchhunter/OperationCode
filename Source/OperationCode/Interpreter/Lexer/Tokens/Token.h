// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Token.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Abstract)
class OPERATIONCODE_API UToken : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	virtual FString GetTokenName() const;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FString TokenName = TEXT("Token");
	
};
