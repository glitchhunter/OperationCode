// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/InterpreterComponent.h"
#include "Tokens/Token.h"
#include "Runtime/CoreUObject/Public/Templates/SubclassOf.h"
#include "Lexer.generated.h"

/**
 * 
 */

USTRUCT()
struct FLexData
{
	GENERATED_BODY()

	FLexData()
	{
		TokenClass = nullptr;
		Sequence = "";
		AllowNextAlphanumeric = false;
	}

	FLexData(FString sequence, TSubclassOf<UToken> tokenClass, bool allowNextAlphanumeric)
	{
		Sequence = sequence;
		TokenClass = tokenClass;
		AllowNextAlphanumeric = allowNextAlphanumeric;
	}

	TSubclassOf<UToken> TokenClass;
	FString Sequence;
	bool AllowNextAlphanumeric;

};

UCLASS(Blueprintable)
class OPERATIONCODE_API ULexer : public UInterpreterComponent
{
	GENERATED_BODY()
	
public:

	ULexer();

	UFUNCTION(BlueprintCallable)
	TArray<UToken*> Tokenize(const FString Source);

	TArray<FLexData> LexData;

protected:

	TCHAR GetCharacter(int32& index, bool AutoIncrement = true);

	UFUNCTION(BlueprintPure)
	bool HasSequence(int32& StartIndex, FString sequence, bool AllowNextAlphanumeric, bool AutoIncrement = true);

	bool LexBool(int32 StartIndex, int32& EndIndex, UToken*& Token);

	bool LexInt(int32 StartIndex, int32& EndIndex, UToken*& Token);

	bool LexFloat(int32 StartIndex, int32& EndIndex, UToken*& Token);

	bool LexString(int32 StartIndex, int32& EndIndex, UToken*& Token);

	bool LexComment(int32 StartIndex, int32& EndIndex, UToken*& Token);

	bool LexIdentifier(int32 StartIndex, int32& EndIndex, UToken*& Token);

	bool LexWhitespace(int32 StartIndex, int32& EndIndex, UToken*& Token);

	bool LexBySequence(int32 StartIndex, FLexData Data, int32& EndIndex, UToken*& Token);

	UToken* Lex(int32& StartIndex);








private:

	TArray<TCHAR> SourceText;
	
	
};
