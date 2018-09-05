// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Parser/AST/Expressions/AST_Expression.h"
#include "AST_Operator.generated.h"

/**
 * 
 */

UENUM()
enum class EOperatorAssociativity : uint8
{
	LeftToRight,
	RightToLeft
};

UCLASS(Abstract)
class OPERATIONCODE_API UAST_Operator : public UAST_Expression
{
	GENERATED_BODY()
	
public:

	EOperatorAssociativity GetAssociativity() const { return Associativity; }

	int32 GetPrecedence() const { return Precedence; }

	virtual bool HasAllArguments() const { return true; }

	virtual void AddArgument(UAST_Expression* Argument) { }

	int32 GetNumberOfArguments() const { return NumberOfArguments; }

	virtual void Analyse(USemanticAnalysisPhase* SemanticAnalysisPhase) override;

	FString GetSign() const { return Sign; }

protected:

	int32 NumberOfArguments;

	EOperatorAssociativity Associativity;

	int32 Precedence;

	FString Sign = "";


	
	
};
