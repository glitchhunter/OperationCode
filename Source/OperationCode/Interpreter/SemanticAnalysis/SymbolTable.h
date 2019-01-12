// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interpreter/FunctionData.h"
#include "ExpressionReturns.h"
#include "SymbolTable.generated.h"

class UAST_ClassDefinition;
class UAST_VariableCall;
class UAST_VariableDefinition;
class UAST_FunctionCall;
class UAST_FunctionDefinition;
class UAST_Return;
class UAST_Break;
class UAST_Continue;
class UAST_Operator;
class UAST_Loop;
class UAST_Expression;
class UValue;




USTRUCT(Blueprintable)
struct FFunctionID
{
	GENERATED_BODY()


	FFunctionID() {}

	FFunctionID(FFunctionSignature functionSignature, UAST_ClassDefinition* classDefinition)
	{
		Signature = functionSignature;
		ClassDefinition = classDefinition;
	}


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAST_ClassDefinition* ClassDefinition;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FFunctionSignature Signature;


	bool operator== (const FFunctionID& other) const
	{
		return ClassDefinition == other.ClassDefinition && Signature == other.Signature;
	}

	bool operator!= (const FFunctionID& other) const
	{
		return !(*this == other);
	}
};


/*
	This is the only way to use the hash correctly that I can think of. FFunctionSignature contains an FString array,
	and TArrays do not seem to play nice with MemCrc32 hashing (They tend to give different result for same values randomly).
*/
FORCEINLINE uint32 GetTypeHash(const FFunctionID& functionID)
{
	return GetTypeHash(functionID.ClassDefinition) + GetTypeHash(functionID.Signature);
	//return FCrc::MemCrc32(&functionID, sizeof(FFunctionID));
}

USTRUCT(BlueprintType)
struct FStaticFunctions
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<UAST_FunctionDefinition*> Functions;
};

USTRUCT(BlueprintType)
struct FStaticVariables
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSet<UAST_VariableDefinition*> Variables;
};

USTRUCT(BlueprintType)
struct FConstructors
{
	GENERATED_BODY()

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TSet<UAST_FunctionDefinition*> constructors;
};


UENUM()
enum class EFunctionMatching
{
	NoMatch,
	WithConversion,
	ExactMatch
};


/**
*
*/
UCLASS(Blueprintable)
class OPERATIONCODE_API USymbolTable : public UObject
{
	GENERATED_BODY()
	
public:

	// Class name, class definition
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FString, UAST_ClassDefinition*> ClassNames;

	// Child, parent
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<UAST_ClassDefinition*, UAST_ClassDefinition*> ClassInheritance;

	// Stored for debug
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<UAST_Expression*, FExpressionReturn> ExpressionReturns;

	// Stores operator overload signatures to function IDs
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FFunctionSignature, FFunctionID> Operators;

	// Stores static functions (Key is class they belong to, empty string means global)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FString, FStaticFunctions> StaticFunctions;

	// Stores static variables (Key is class they belong to, empty string means global)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FString, FStaticVariables> StaticVariables;

	// not used
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<UAST_Return*, UAST_FunctionDefinition*> Returns;

	// not used
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<UAST_Break*, UAST_Loop*> Breaks;

	// not used
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<UAST_Continue*, UAST_Loop*> Continues;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<FFunctionID, UAST_FunctionDefinition*> FunctionIDs;

	//Stores static function calls for quick lookup at runtime
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<UAST_FunctionCall*, UAST_FunctionDefinition*> StaticFunctionCalls;

	//Stores static variable calls for quick lookup at runtime
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<UAST_VariableCall*, UAST_VariableDefinition*> StaticVariableCalls;

	// Stores constructors
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TMap<UAST_ClassDefinition*, FConstructors> Constructors;

	// The initial owner
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UValue* TopOwner;

	// Variables that are owned by the top owner
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSet<UAST_VariableCall*> TopOwnedVariableCalls;

	// Functions that are owned by the top owner
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSet<UAST_FunctionCall*> TopOwnedFunctionCalls;





	UFUNCTION()
	bool IsInstanceUnique(UAST_ClassDefinition* ClassDefinition);

	UFUNCTION()
	bool IsInstanceUniqueByName(FString ClassDefinitionName);

	UFUNCTION(BlueprintCallable)
	FString DebugPrintFunctions();

	UFUNCTION(BlueprintCallable)
	bool IsChildOfByName(FString child, FString parent) const;

	UFUNCTION(BlueprintCallable)
	bool IsChildOf(UAST_ClassDefinition* child, UAST_ClassDefinition* parent) const;

	UFUNCTION(BlueprintCallable)
	EFunctionMatching GetFunctionMatch(UAST_FunctionCall* FunctionCall, FFunctionSignature signature, FString ElementType);

	UFUNCTION(BlueprintCallable)
	TArray<UAST_FunctionDefinition*> GetFunctionDefinitions(UAST_FunctionCall* FunctionCall, UAST_ClassDefinition* OwningClass, FString elementType,  bool ReturnOnFirstMatch);

	UFUNCTION()
	UAST_FunctionDefinition* GetOverloadedOperator(FFunctionSignature Signature);


	UFUNCTION(BlueprintCallable)
	bool CanConvertTypes(FString From, FString To);

	UFUNCTION(BlueprintCallable)
	UAST_FunctionDefinition* GetImplicitConverterByName(FString From, FString To);

	UFUNCTION(BlueprintCallable)
	UAST_FunctionDefinition* GetImplicitConverter(UAST_ClassDefinition* From, UAST_ClassDefinition* To);

	UFUNCTION(BlueprintCallable)
	UAST_FunctionDefinition* GetExplicitConverterByName(FString From, FString To);

	UFUNCTION(BlueprintCallable)
	UAST_FunctionDefinition* GetExplicitConverter(UAST_ClassDefinition* From, UAST_ClassDefinition* To);

	UFUNCTION()
	UAST_FunctionDefinition* GetConstructor(FString className, TArray<FParamSignature> paramSig);

private:

	bool DoParameterTypesMatch(UAST_FunctionDefinition* functionDefinition, FFunctionSignature signature);

	UAST_FunctionDefinition* GetSpecialOperator(FFunctionSignature signature);
};
