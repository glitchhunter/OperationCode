// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/Implicit/ImplicitRTS.h"
#include "RTS_InstanceCreator.generated.h"

class UBoolInstance;
class UIntInstance;
class UFloatInstance;
class UStringInstance;
class UArrayInstance;
class UAST_ClassDefinition;

/**
 * 
 */
UCLASS()
class URTS_InstanceCreator : public UImplicitRTS
{
	GENERATED_BODY()
	
public:

	void RunStep() override;

	void SetValues(FString type, bool isArray, TArray<UValue*> constructorParameters);

	UFUNCTION(BlueprintCallable)
	static UBoolInstance* CreateBoolValue(UCodeRunner* activeCodeRunner, bool Value = false);

	UFUNCTION(BlueprintCallable)
	static UIntInstance* CreateIntValue(UCodeRunner* activeCodeRunner, int32 Value = 0);

	UFUNCTION(BlueprintCallable)
	static UFloatInstance* CreateFloatValue(UCodeRunner* activeCodeRunner, float Value = 0.0f);

	UFUNCTION(BlueprintCallable)
	static UStringInstance* CreateStringValue(UCodeRunner* activeCodeRunner, FString Value = "");

	UFUNCTION(BlueprintCallable)
	static UValue* CreateNullValue(UCodeRunner* activeCodeRunner, FString type);

	UFUNCTION(BlueprintCallable)
	static UArrayInstance* CreateArrayValue(UCodeRunner* activeCodeRunner, FString type, TArray<UValue*> Values);

	// Return a predefined type if the given type is a bool, int, float or string.
	// Otherwise it returns a nullptr.
	static UValue* CreatePredefinedType(UCodeRunner* activeCodeRunner, FString type);





protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FString Type;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UValue*> ConstructorParameters;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UValue* NewValue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 VariableIndex;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadonly)
	UAST_ClassDefinition* Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 SkippedVariables;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool IsArray;

	bool ExpectingInitExpression;

	bool ValueAssigned;

	bool ConstructorStarted;
	
};
