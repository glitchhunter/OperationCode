// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/Implicit/ImplicitRTS.h"
#include "RTS_ChainedFunctionCall.generated.h"

class UAST_FunctionDefinition;

/**
 * 
 */
UCLASS()
class URTS_ChainedFunctionCall : public UImplicitRTS
{
	GENERATED_BODY()
	
public:

	virtual void RunStep() override;

	UFUNCTION(BlueprintCallable)
	void SetData(UAST_FunctionDefinition* functionDefinition, UValue* owner, TArray<UValue*> values);

	UFUNCTION(BlueprintCallable, Category = "WhyWontYouWork")
		void SetCodeRunner(UCodeRunner* codeRun);


protected:


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UAST_FunctionDefinition* FunctionDefinition;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UValue*> Values;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ArgumentIndex;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool ConvertingValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UValue* Owner;
	
};
