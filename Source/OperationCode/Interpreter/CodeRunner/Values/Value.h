// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Variables.h"
#include "Value.generated.h"

class UCodeRunner;


/**
 * 
 */
UCLASS(Blueprintable)
class OPERATIONCODE_API UValue : public UObject
{
	GENERATED_BODY()
	
public:

	virtual FString GetType() const { return Type; }

	virtual UValue* GetVariable(FString VarName);

	virtual bool IsNullable() const { return ChachedIsNullable; }

	virtual void Init(FString ValueType, UCodeRunner* codeRunner);

	UFUNCTION(BlueprintCallable)
	void CreateVariables();

	virtual bool IsNull() const { return Variables == nullptr; }

	void AddVariable(FString Varname, UValue* value) { Variables->Variables.Add(Varname, value); }

	UFUNCTION(BlueprintNativeEvent)
	UValue* Duplicate();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FString Type;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UVariables* Variables;

protected:

	UPROPERTY()
	UCodeRunner* CodeRunner;
	
	bool ChachedIsNullable;
	
};
