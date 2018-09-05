// Fill out your copyright notice in the Description page of Project Settings.

#include "Lexer.h"

#include "Tokens/Brackets/T_ClosedCurlyBracket.h"
#include "Tokens/Brackets/T_OpenCurlyBracket.h"
#include "Tokens/Brackets/T_ClosedRoundBracket.h"
#include "Tokens/Brackets/T_OpenRoundBracket.h"
#include "Tokens/Brackets/T_ClosedSquareBracket.h"
#include "Tokens/Brackets/T_OpenSquareBracket.h"

#include "Tokens/Keywords/T_Array.h"
#include "Tokens/Keywords/T_Class.h"
#include "Tokens/Keywords/T_Do.h"
#include "Tokens/Keywords/T_For.h"
#include "Tokens/Keywords/T_If.h"
#include "Tokens/Keywords/T_Else.h"
#include "Tokens/Keywords/T_Return.h"
#include "Tokens/Keywords/T_While.h"
#include "Tokens/Keywords/T_Inherits.h"
#include "Tokens/Keywords/T_Break.h"
#include "Tokens/Keywords/T_Continue.h"
#include "Tokens/Keywords/T_OperatorKeyword.h"
#include "Tokens/Keywords/T_Const.h"
#include "Tokens/Keywords/T_Static.h"
#include "Tokens/Keywords/T_Convert.h"
#include "Tokens/Keywords/T_Auto.h"
#include "Tokens/Keywords/T_Constructor.h"

#include "Tokens/Literals/T_BoolLiteral.h"
#include "Tokens/Literals/T_FloatLiteral.h"
#include "Tokens/Literals/T_IntLiteral.h"
#include "Tokens/Literals/T_StringLiteral.h"
#include "Tokens/Literals/T_Nullptr.h"

#include "Tokens/Operators/Arithmetic/T_Divide.h"
#include "Tokens/Operators/Arithmetic/T_Minus.h"
#include "Tokens/Operators/Arithmetic/T_MinusMinus.h"
#include "Tokens/Operators/Arithmetic/T_Modulo.h"
#include "Tokens/Operators/Arithmetic/T_Multiply.h"
#include "Tokens/Operators/Arithmetic/T_Plus.h"
#include "Tokens/Operators/Arithmetic/T_PlusPlus.h"

#include "Tokens/Operators/Assignments/T_Equal.h"
#include "Tokens/Operators/Assignments/AugmentedAssignments/T_DivideEqual.h"
#include "Tokens/Operators/Assignments/AugmentedAssignments/T_MinusEqual.h"
#include "Tokens/Operators/Assignments/AugmentedAssignments/T_ModuloEqual.h"
#include "Tokens/Operators/Assignments/AugmentedAssignments/T_MultiplyEqual.h"
#include "Tokens/Operators/Assignments/AugmentedAssignments/T_PlusEqual.h"

#include "Tokens/Operators/Logical/T_And.h"
#include "Tokens/Operators/Logical/T_Not.h"
#include "Tokens/Operators/Logical/T_Or.h"

#include "Tokens/Operators/Relational/T_Greater.h"
#include "Tokens/Operators/Relational/T_GreaterOrEqual.h"
#include "Tokens/Operators/Relational/T_Less.h"
#include "Tokens/Operators/Relational/T_LessOrEqual.h"
#include "Tokens/Operators/Relational/T_NotEqualTo.h"
#include "Tokens/Operators/Relational/T_EqualTo.h"
#include "Tokens/Operators/T_Dot.h"

#include "Tokens/Specials/T_Ampersand.h"
#include "Tokens/Specials/T_Colon.h"
#include "Tokens/Specials/T_Comma.h"
#include "Tokens/Specials/T_Comment.h"
#include "Tokens/Specials/T_Identifier.h"
#include "Tokens/Specials/T_Semicolon.h"
#include "Tokens/Specials/T_Whitespace.h"
#include "Tokens/Specials/T_DoubleColon.h"


ULexer::ULexer()
{
	LexData.Add(FLexData("array", UT_Array::StaticClass(), false));
	LexData.Add(FLexData("class", UT_Class::StaticClass(), false));
	LexData.Add(FLexData("do", UT_Do::StaticClass(), false));
	LexData.Add(FLexData("for", UT_For::StaticClass(), false));
	LexData.Add(FLexData("if", UT_If::StaticClass(), false));
	LexData.Add(FLexData("else", UT_Else::StaticClass(), false));
	LexData.Add(FLexData("return", UT_Return::StaticClass(), false));
	LexData.Add(FLexData("while", UT_While::StaticClass(), false));
	LexData.Add(FLexData("inherits", UT_Inherits::StaticClass(), false));
	LexData.Add(FLexData("break", UT_Break::StaticClass(), false));
	LexData.Add(FLexData("continue", UT_Continue::StaticClass(), false));
	LexData.Add(FLexData("operator", UT_OperatorKeyword::StaticClass(), false));
	LexData.Add(FLexData("static", UT_Static::StaticClass(), false));
	LexData.Add(FLexData("convert", UT_Convert::StaticClass(), false));
	LexData.Add(FLexData("auto", UT_Auto::StaticClass(), false));
	LexData.Add(FLexData("constructor", UT_Constructor::StaticClass(), false));
	LexData.Add(FLexData("const", UT_Const::StaticClass(), false));
	LexData.Add(FLexData("nullptr", UT_Nullptr::StaticClass(), false));

	LexData.Add(FLexData("}", UT_ClosedCurlyBracket::StaticClass(), true));
	LexData.Add(FLexData("{", UT_OpenCurlyBracket::StaticClass(), true));
	LexData.Add(FLexData(")", UT_ClosedRoundBracket::StaticClass(), true));
	LexData.Add(FLexData("(", UT_OpenRoundBracket::StaticClass(), true));
	LexData.Add(FLexData("]", UT_ClosedSquareBracket::StaticClass(), true));
	LexData.Add(FLexData("[", UT_OpenSquareBracket::StaticClass(), true));

	LexData.Add(FLexData(">=", UT_GreaterOrEqual::StaticClass(), true));
	LexData.Add(FLexData(">", UT_Greater::StaticClass(), true));
	LexData.Add(FLexData("<=", UT_LessOrEqual::StaticClass(), true));
	LexData.Add(FLexData("<", UT_Less::StaticClass(), true));
	LexData.Add(FLexData("==", UT_EqualTo::StaticClass(), true));
	LexData.Add(FLexData("!=", UT_NotEqualTo::StaticClass(), true));

	LexData.Add(FLexData("/=", UT_DivideEqual::StaticClass(), true));
	LexData.Add(FLexData("-=", UT_MinusEqual::StaticClass(), true));
	LexData.Add(FLexData("%=", UT_ModuloEqual::StaticClass(), true));
	LexData.Add(FLexData("*=", UT_MultiplyEqual::StaticClass(), true));
	LexData.Add(FLexData("+=", UT_PlusEqual::StaticClass(), true));
	LexData.Add(FLexData("=", UT_Equal::StaticClass(), true));

	LexData.Add(FLexData("/", UT_Divide::StaticClass(), true));
	LexData.Add(FLexData("--", UT_MinusMinus::StaticClass(), true));
	LexData.Add(FLexData("-", UT_Minus::StaticClass(), true));
	LexData.Add(FLexData("%", UT_Modulo::StaticClass(), true));
	LexData.Add(FLexData("*", UT_Multiply::StaticClass(), true));
	LexData.Add(FLexData("++", UT_PlusPlus::StaticClass(), true));
	LexData.Add(FLexData("+", UT_Plus::StaticClass(), true));

	LexData.Add(FLexData("&&", UT_And::StaticClass(), true));
	LexData.Add(FLexData("||", UT_Or::StaticClass(), true));
	LexData.Add(FLexData("!", UT_Not::StaticClass(), true));

	LexData.Add(FLexData("&", UT_Ampersand::StaticClass(), true));
	LexData.Add(FLexData("::", UT_DoubleColon::StaticClass(), true));
	LexData.Add(FLexData(":", UT_Colon::StaticClass(), true));
	LexData.Add(FLexData(",", UT_Comma::StaticClass(), true));
	LexData.Add(FLexData(".", UT_Dot::StaticClass(), true));
	LexData.Add(FLexData(";", UT_Semicolon::StaticClass(), true));
}

TCHAR ULexer::GetCharacter(int32& index, bool AutoIncrement /* = true */)
{
	if (!SourceText.IsValidIndex(index)) return '\0';

	TCHAR result = SourceText[index];
	if (AutoIncrement) ++index;
	return result;
}

bool ULexer::HasSequence(int32& StartIndex, FString sequence, bool AllowNextAlphanumeric, bool AutoIncrement /* = true */)
{
	TArray<TCHAR> CharSequence = sequence.GetCharArray();
	for (int32 i = 0; i < CharSequence.Num() - 1; ++i)
	{
		if (!SourceText.IsValidIndex(StartIndex + i) || CharSequence[i] != SourceText[StartIndex + i]) return false;
	}

	// If AllowNextAlphanumeric is false, and next character is alphanumeric or underscore, then return false
	if (!AllowNextAlphanumeric && SourceText.IsValidIndex(CharSequence.Num() - 1 + StartIndex) 
		&& (TChar<TCHAR>::IsAlnum(SourceText[CharSequence.Num() - 1 + StartIndex]) || TChar<TCHAR>::IsUnderscore(SourceText[CharSequence.Num() - 1 + StartIndex])))
		return false;

	if (AutoIncrement) StartIndex += CharSequence.Num() - 1;
	return true;
}

UToken* ULexer::Lex(int32& StartIndex)
{
	UToken* Token = nullptr;

	if (LexComment(StartIndex, StartIndex, Token)) return Token;
	if (LexBool(StartIndex, StartIndex, Token)) return Token;
	if (LexFloat(StartIndex, StartIndex, Token)) return Token;
	if (LexInt(StartIndex, StartIndex, Token)) return Token;
	if (LexString(StartIndex, StartIndex, Token)) return Token;
	if (LexWhitespace(StartIndex, StartIndex, Token)) return Token;

	for (FLexData currentLexData : LexData)
	{
		if (LexBySequence(StartIndex, currentLexData, StartIndex, Token)) return Token;
	}

	if (LexIdentifier(StartIndex, StartIndex, Token)) return Token;

	return nullptr;
}

bool ULexer::LexBool(int32 StartIndex, int32& EndIndex, UToken*& Token)
{
	if (HasSequence(StartIndex, "true", false))
	{
		UT_BoolLiteral* BoolLiteral = NewObject<UT_BoolLiteral>(GetInterpreter());
		BoolLiteral->Value = true;
		Token = BoolLiteral;
		EndIndex = StartIndex;
		return true;
	}
	
	if (HasSequence(StartIndex, "false", false))
	{
		UT_BoolLiteral* BoolLiteral = NewObject<UT_BoolLiteral>(GetInterpreter());
		BoolLiteral->Value = false;
		Token = BoolLiteral;
		EndIndex = StartIndex;
		return true;
	}

	return false;
}

bool ULexer::LexInt(int32 StartIndex, int32& EndIndex, UToken*& Token)
{
	FString IntAsString = "";
	while (SourceText.IsValidIndex(StartIndex) && TChar<TCHAR>::IsDigit(SourceText[StartIndex]))
	{
		IntAsString.AppendChar(GetCharacter(StartIndex));
	}

	if (!IntAsString.IsNumeric()) return false;

	UT_IntLiteral* IntLiteral = NewObject<UT_IntLiteral>(GetInterpreter());
	IntLiteral->Value = FCString::Atoi(*IntAsString);
	Token = IntLiteral;
	EndIndex = StartIndex;
	return true;
}

bool ULexer::LexFloat(int32 StartIndex, int32& EndIndex, UToken*& Token)
{
	FString FloatAsString = "";
	while (SourceText.IsValidIndex(StartIndex) && TChar<TCHAR>::IsDigit(SourceText[StartIndex]))
	{
		FloatAsString.AppendChar(GetCharacter(StartIndex));
	}

	if (!HasSequence(StartIndex, ".", true)) return false;
	FloatAsString += ".";

	while (SourceText.IsValidIndex(StartIndex) && TChar<TCHAR>::IsDigit(SourceText[StartIndex]))
	{
		FloatAsString.AppendChar(GetCharacter(StartIndex));
	}

	if (FloatAsString == "" || FloatAsString == "." || !FloatAsString.IsNumeric()) return false;

	UT_FloatLiteral* FloatLiteral = NewObject<UT_FloatLiteral>(GetInterpreter());
	FloatLiteral->Value = FCString::Atof(*FloatAsString);
	Token = FloatLiteral;
	EndIndex = StartIndex;
	return true;
}

bool ULexer::LexString(int32 StartIndex, int32& EndIndex, UToken*& Token)
{
	FString result = "";

	if (!HasSequence(StartIndex, "\"", true)) return false;

	while (SourceText.IsValidIndex(StartIndex))
	{
		if (HasSequence(StartIndex, "\n", true)) return false;
		if (HasSequence(StartIndex, "\"", true))
		{
			UT_StringLiteral* StringLiteral = NewObject<UT_StringLiteral>(GetInterpreter());
			StringLiteral->Value = result;
			EndIndex = StartIndex;
			Token = StringLiteral;
			return true;
		}

		result += GetCharacter(StartIndex);
	}

	return false;
}

bool ULexer::LexComment(int32 StartIndex, int32& EndIndex, UToken*& Token)
{
	FString comment = "";
	if (HasSequence(StartIndex, "//", true))
	{
		while (SourceText.IsValidIndex(StartIndex))
		{
			TCHAR current = GetCharacter(StartIndex, false);
			if (TChar<TCHAR>::IsLinebreak(current)) break;

			comment.AppendChar(current);
			StartIndex++;
		}
		UT_Comment* CommentToken = NewObject<UT_Comment>(GetInterpreter());
		CommentToken->Comment = comment;
		Token = CommentToken;
		EndIndex = StartIndex;
		return true;
	}
	else if (HasSequence(StartIndex, "/*", true))
	{
		while (SourceText.IsValidIndex(StartIndex + 1))
		{
			if (HasSequence(StartIndex, "*/", true))
			{
				UT_Comment* CommentToken = NewObject<UT_Comment>(GetInterpreter());
				CommentToken->Comment = comment;
				Token = CommentToken;
				EndIndex = StartIndex;
				return true;
			}
			TCHAR current = GetCharacter(StartIndex);
			comment.AppendChar(current);
		}
		return false;
	}
	return false;
}

bool ULexer::LexIdentifier(int32 StartIndex, int32& EndIndex, UToken*& Token)
{
	if (!SourceText.IsValidIndex(StartIndex)) return false;

	FString ID = "";
	TCHAR current = GetCharacter(StartIndex);

	if (!TChar<TCHAR>::IsUnderscore(current) && !TChar<TCHAR>::IsAlpha(current)) return false;
	ID.AppendChar(current);

	while (SourceText.IsValidIndex(StartIndex))
	{
		current = GetCharacter(StartIndex, false);
		if (!TChar<TCHAR>::IsUnderscore(current) && !TChar<TCHAR>::IsAlnum(current)) break;
		ID.AppendChar(current);
		StartIndex++;
	}

	UT_Identifier* Identifier = NewObject<UT_Identifier>(GetInterpreter());
	Identifier->ID = ID;
	Token = Identifier;
	EndIndex = StartIndex;
	return true;
}

bool ULexer::LexWhitespace(int32 StartIndex, int32& EndIndex, UToken*& Token)
{
	if (!SourceText.IsValidIndex(StartIndex)) return false;

	TCHAR c = GetCharacter(StartIndex);
	if (!TChar<TCHAR>::IsWhitespace(c)) return false;

	EndIndex = StartIndex;
	Token = NewObject<UT_Whitespace>(GetInterpreter());
	return true;
}

bool ULexer::LexBySequence(int32 StartIndex, FLexData Data, int32& EndIndex, UToken*& Token)
{
	if (!HasSequence(StartIndex, Data.Sequence, Data.AllowNextAlphanumeric)) return false;

	Token = NewObject<UToken>(GetInterpreter(), Data.TokenClass);
	EndIndex = StartIndex;
	return true;
}


TArray<UToken*> ULexer::Tokenize(const FString Source)
{

	SourceText = Source.GetCharArray();
	TArray<UToken*> result;
	int32 index = 0;

	while (SourceText.IsValidIndex(index) && SourceText[index] != '\0')
	{
		UToken* tok = Lex(index);
		if (tok)
		{
			result.Add(tok);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Not all tokens processed, last token index is %d"), index);
			return result;
		}
	}

	return result;
}


