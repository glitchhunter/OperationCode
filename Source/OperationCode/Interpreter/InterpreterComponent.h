// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interpreter.h"
#include "InterpreterComponent.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class OPERATIONCODE_API UInterpreterComponent : public UObject
{
	GENERATED_BODY()
	
public:

	void Init(UInterpreter* interpreter) { Interpreter = interpreter; }

	UFUNCTION(BlueprintPure)
	UInterpreter* GetInterpreter() { return Interpreter; }

	virtual void ThrowError(FString ErrorMessage);

	virtual void ThrowWarning(FString WarningMessage);

	virtual void Clear();

	virtual UWorld* GetWorld() const override;

	bool HasErrors() const { return ThrewError; }

protected:

	UPROPERTY()
	UInterpreter* Interpreter;

	UPROPERTY()
		bool ThrewError;
	
	
};
