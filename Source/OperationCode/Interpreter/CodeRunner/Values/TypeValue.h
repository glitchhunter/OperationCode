// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/Values/Value.h"
#include "TypeValue.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UTypeValue : public UValue
{
	GENERATED_BODY()

public:

	virtual bool IsNull() const override { return false; }

	virtual bool IsNullable() const override { return false; }

	virtual void Init(FString ValueType, UCodeRunner* codeRunner) override;
	
	
};
