// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "FunctionData.generated.h"

USTRUCT(Blueprintable)
struct FParamSignature
{
	GENERATED_BODY()

		FParamSignature() {}

	FParamSignature(FString type, bool isArray)
	{
		Type = type;
		IsArray = isArray;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FString Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsArray;

	FString ToString()
	{
		FString boolString = IsArray ? TEXT("true") : TEXT("false");
		return Type + boolString;
	}


	// operator== and GethashType make this struct usable as key in TMaps
	bool operator== (const FParamSignature& rhs) const
	{
		return IsArray == rhs.IsArray && Type == rhs.Type;
	}

	bool operator!= (const FParamSignature& rhs) const
	{
		return !(*this == rhs);
	}

};

FORCEINLINE uint32 GetTypeHash(const FParamSignature& signature)
{
	return FCrc::MemCrc32(&signature, sizeof(FParamSignature));
}


/**
 * Signature of a function. Functions are differentiated only by name and parameter types.
 */
USTRUCT(Blueprintable)
struct FFunctionSignature
{
	GENERATED_BODY()

	FFunctionSignature() { }

	FFunctionSignature(FString Name, TArray<FParamSignature> ParamSigs)
	{
		FunctionName = Name;
		ParameterSignatures = ParamSigs;
	}



	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FunctionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FParamSignature> ParameterSignatures;


	// operator== and GethashType make this struct usable as key in TMaps
	bool operator== (const FFunctionSignature& rhs) const
	{
		if (FunctionName != rhs.FunctionName) return false;
		if (ParameterSignatures.Num() != rhs.ParameterSignatures.Num()) return false;

		for (int i = 0; i < ParameterSignatures.Num(); ++i)
		{
			if (ParameterSignatures[i] != rhs.ParameterSignatures[i]) return false;
		}

		return true;
	}

	bool operator!= (const FFunctionSignature& rhs) const
	{
		return !(*this == rhs);
	}


};

/*
	Takes the function name and argument types, stores them in one string and then hashes that string.
	This has to be done since arrays themselves return different hashes even with same values.
	So using MemCrc32 hash function is not possible. This also means that any struct or class using this
	struct also cannot use MemCrc32 function. It is an ugly workaround, but better to have ugly working code,
	then pretty code that does not work.
	Wow, I really am becoming a real programmer...
*/
FORCEINLINE uint32 GetTypeHash(const FFunctionSignature& signature)
{
	FString temp = "";
	for (FParamSignature current : signature.ParameterSignatures) temp += current.ToString();
	return GetTypeHash(signature.FunctionName + temp);
}

/**
 * Contains all data necesary to represent a parameter (Type, name, is it passed by reference and is it const)
 */
USTRUCT(Blueprintable)
struct FParameterData
{
	GENERATED_BODY()

	FParameterData() {}

	FParameterData(FString type, FString name, bool isPassByReference, bool isConst, bool isArray)
	{
		Type = type;
		Name = name;
		IsPassByReference = isPassByReference;
		IsConst = isConst;
		IsArray = isArray;
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsPassByReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsConst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsArray;
};

/**
 * Contains all data that represent a function header
 */
USTRUCT(Blueprintable)
struct FFunctionData
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString FunctionName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FParameterData> ParameterData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ReturnType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool ReturnsArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsReturnPassByReference;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsConst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsFinal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsStatic;

	FFunctionSignature GetSignature() const
	{
		TArray<FParamSignature> paramSigs;
		for (FParameterData currentParamData : ParameterData)
		{
			paramSigs.Add(FParamSignature(currentParamData.Type, currentParamData.IsArray));
		}

		return FFunctionSignature(FunctionName, paramSigs);
	}


};