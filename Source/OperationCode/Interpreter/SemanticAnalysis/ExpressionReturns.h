// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ExpressionReturns.generated.h"

UENUM(BlueprintType)
enum class EReturnMode : uint8
{
	Invalid,
	Type,
	Value,
	Array
};

USTRUCT(BlueprintType)
struct FExpressionReturn
{

	GENERATED_BODY()

public:

	FExpressionReturn()
	{
		Clear();
	}

	FExpressionReturn(FString returnType, EReturnMode returnMode)
	{
		ReturnType = returnType;
		ReturnMode = returnMode;
	}


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ReturnType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EReturnMode ReturnMode;

	// operator== and GethashType make this struct usable as key in TMaps
	bool operator== (const FExpressionReturn& rhs) const
	{
		if (ReturnMode != rhs.ReturnMode) return false;
		if (ReturnType != rhs.ReturnType) return false;

		return true;
	}

	bool operator!= (const FExpressionReturn& rhs) const
	{
		return !(*this == rhs);
	}

	friend uint32 GetTypeHash(const FExpressionReturn& ExpressionReturn)
	{
		return FCrc::MemCrc32(&ExpressionReturn, sizeof(FExpressionReturn));
	}

	
	FString AsString() const
	{
		FString result = ReturnType;
		switch (ReturnMode)
		{
		case EReturnMode::Type:
			result += " type";
			break;
		case EReturnMode::Value:
			result += " value";
			break;
		case EReturnMode::Array:
			result += " array";
			break;
		default:
			break;
		}
		return result;
	}

	void Clear()
	{
		ReturnType = "";
		ReturnMode = EReturnMode::Invalid;
	}

	bool IsClear() const
	{
		return ReturnMode == EReturnMode::Invalid;
	}

	bool ReturnsValue() const
	{
		return ReturnMode == EReturnMode::Value;
	}

	bool ReturnsType() const
	{
		return ReturnMode == EReturnMode::Type;
	}

	bool ReturnsArray() const
	{
		return ReturnMode == EReturnMode::Array;
	}
};