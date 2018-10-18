// Fill out your copyright notice in the Description page of Project Settings.

#include "Parser.h"


#include "Interpreter/Lexer/Tokens/Brackets/T_ClosedCurlyBracket.h"
#include "Interpreter/Lexer/Tokens/Brackets/T_ClosedRoundBracket.h"
#include "Interpreter/Lexer/Tokens/Brackets/T_ClosedSquareBracket.h"
#include "Interpreter/Lexer/Tokens/Brackets/T_OpenCurlyBracket.h"
#include "Interpreter/Lexer/Tokens/Brackets/T_OpenRoundBracket.h"
#include "Interpreter/Lexer/Tokens/Brackets/T_OpenSquareBracket.h"

#include "Interpreter/Lexer/Tokens/Keywords/T_Class.h"
#include "Interpreter/Lexer/Tokens/Keywords/T_Do.h"
#include "Interpreter/Lexer/Tokens/Keywords/T_For.h"
#include "Interpreter/Lexer/Tokens/Keywords/T_If.h"
#include "Interpreter/Lexer/Tokens/Keywords/T_Else.h"
#include "Interpreter/Lexer/Tokens/Keywords/T_Return.h"
#include "Interpreter/Lexer/Tokens/Keywords/T_While.h"
#include "Interpreter/Lexer/Tokens/Keywords/T_Inherits.h"
#include "Interpreter/Lexer/Tokens/Keywords/T_Break.h"
#include "Interpreter/Lexer/Tokens/Keywords/T_Continue.h"
#include "Interpreter/Lexer/Tokens/Keywords/T_OperatorKeyword.h"
#include "Interpreter/Lexer/Tokens/Keywords/T_Const.h"
#include "Interpreter/Lexer/Tokens/Keywords/T_Static.h"
#include "Interpreter/Lexer/Tokens/Keywords/T_Convert.h"
#include "Interpreter/Lexer/Tokens/Keywords/T_Auto.h"
#include "Interpreter/Lexer/Tokens/Keywords/T_Constructor.h"
#include "Interpreter/Lexer/Tokens/Keywords/T_Final.h"
#include "Interpreter/Lexer/Tokens/Keywords/T_Array.h"

#include "Interpreter/Lexer/Tokens/Literals/T_BoolLiteral.h"
#include "Interpreter/Lexer/Tokens/Literals/T_IntLiteral.h"
#include "Interpreter/Lexer/Tokens/Literals/T_FloatLiteral.h"
#include "Interpreter/Lexer/Tokens/Literals/T_StringLiteral.h"
#include "Interpreter/Lexer/Tokens/Literals/T_Nullptr.h"

#include "Interpreter/Lexer/Tokens/Operators/Arithmetic/T_Divide.h"
#include "Interpreter/Lexer/Tokens/Operators/Arithmetic/T_Minus.h"
#include "Interpreter/Lexer/Tokens/Operators/Arithmetic/T_MinusMinus.h"
#include "Interpreter/Lexer/Tokens/Operators/Arithmetic/T_Modulo.h"
#include "Interpreter/Lexer/Tokens/Operators/Arithmetic/T_Multiply.h"
#include "Interpreter/Lexer/Tokens/Operators/Arithmetic/T_Plus.h"
#include "Interpreter/Lexer/Tokens/Operators/Arithmetic/T_PlusPlus.h"

#include "Interpreter/Lexer/Tokens/Operators/Logical/T_And.h"
#include "Interpreter/Lexer/Tokens/Operators/Logical/T_Not.h"
#include "Interpreter/Lexer/Tokens/Operators/Logical/T_Or.h"

#include "Interpreter/Lexer/Tokens/Operators/Relational/T_EqualTo.h"
#include "Interpreter/Lexer/Tokens/Operators/Relational/T_Greater.h"
#include "Interpreter/Lexer/Tokens/Operators/Relational/T_GreaterOrEqual.h"
#include "Interpreter/Lexer/Tokens/Operators/Relational/T_Less.h"
#include "Interpreter/Lexer/Tokens/Operators/Relational/T_LessOrEqual.h"
#include "Interpreter/Lexer/Tokens/Operators/Relational/T_NotEqualTo.h"

#include "Interpreter/Lexer/Tokens/Operators/Assignments/T_Equal.h"
#include "Interpreter/Lexer/Tokens/Operators/Assignments/AugmentedAssignments/T_DivideEqual.h"
#include "Interpreter/Lexer/Tokens/Operators/Assignments/AugmentedAssignments/T_MinusEqual.h"
#include "Interpreter/Lexer/Tokens/Operators/Assignments/AugmentedAssignments/T_ModuloEqual.h"
#include "Interpreter/Lexer/Tokens/Operators/Assignments/AugmentedAssignments/T_MultiplyEqual.h"
#include "Interpreter/Lexer/Tokens/Operators/Assignments/AugmentedAssignments/T_PlusEqual.h"
#include "Interpreter/Lexer/Tokens/Operators/T_Dot.h"

#include "Interpreter/Lexer/Tokens/Specials/T_Comma.h"
#include "Interpreter/Lexer/Tokens/Specials/T_Comment.h"
#include "Interpreter/Lexer/Tokens/Specials/T_Identifier.h"
#include "Interpreter/Lexer/Tokens/Specials/T_Semicolon.h"
#include "Interpreter/Lexer/Tokens/Specials/T_Whitespace.h"
#include "Interpreter/Lexer/Tokens/Specials/T_Ampersand.h"


#include "AST/AST_Main.h"
#include "AST/AST_Return.h"
#include "AST/AST_Scope.h"
#include "AST/AST_Break.h"
#include "AST/AST_Continue.h"

#include "AST/Definition/AST_ClassDefinition.h"
#include "AST/Definition/AST_FunctionDefinition.h"
#include "AST/Definition/AST_VariableDefinition.h"

#include "AST/Expressions/Calls/AST_FunctionCall.h"
#include "AST/Expressions/Calls/AST_VariableCall.h"

#include "AST/Expressions/Operators/TwoArguments/AST_And.h"
#include "AST/Expressions/Operators/OneArgument/AST_DecrementPrefix.h"
#include "AST/Expressions/Operators/OneArgument/AST_DecrementSufix.h"
#include "AST/Expressions/Operators/OneArgument/AST_IncrementPrefix.h"
#include "AST/Expressions/Operators/OneArgument/AST_IncrementSufix.h"
#include "AST/Expressions/Operators/OneArgument/AST_Not.h"
#include "AST/Expressions/Operators/OneArgument/AST_UnaryMinus.h"
#include "AST/Expressions/Operators/OneArgument/AST_UnaryPlus.h"

#include "AST/Expressions/Operators/TwoArguments/AST_Addition.h"
#include "AST/Expressions/Operators/TwoArguments/AST_Division.h"
#include "AST/Expressions/Operators/TwoArguments/AST_EqualTo.h"
#include "AST/Expressions/Operators/TwoArguments/AST_Greater.h"
#include "AST/Expressions/Operators/TwoArguments/AST_GreaterOrEqual.h"
#include "AST/Expressions/Operators/TwoArguments/AST_Less.h"
#include "AST/Expressions/Operators/TwoArguments/AST_LessOrEqual.h"
#include "AST/Expressions/Operators/TwoArguments/AST_MemberAccess.h"
#include "AST/Expressions/Operators/TwoArguments/AST_Modulo.h"
#include "AST/Expressions/Operators/TwoArguments/AST_Multiplication.h"
#include "AST/Expressions/Operators/TwoArguments/AST_NotEqualTo.h"
#include "AST/Expressions/Operators/TwoArguments/AST_Or.h"
#include "AST/Expressions/Operators/TwoArguments/AST_Subtraction.h"

#include "AST/Expressions/Operators/TwoArguments/Assignment/AST_DirectAssignment.h"
#include "AST/Expressions/Operators/TwoArguments/Assignment/CompoundAssignment/AST_DivideEqual.h"
#include "AST/Expressions/Operators/TwoArguments/Assignment/CompoundAssignment/AST_MinusEqual.h"
#include "AST/Expressions/Operators/TwoArguments/Assignment/CompoundAssignment/AST_ModuloEqual.h"
#include "AST/Expressions/Operators/TwoArguments/Assignment/CompoundAssignment/AST_MultiplyEqual.h"
#include "AST/Expressions/Operators/TwoArguments/Assignment/CompoundAssignment/AST_PlusEqual.h"

#include "AST/FlowControl/Loops/AST_DoWhile.h"
#include "AST/FlowControl/Loops/AST_For.h"
#include "AST/FlowControl/Loops/AST_While.h"
#include "AST/FlowControl/AST_If.h"

#include "AST/Expressions/Literals/AST_BoolLiteral.h"
#include "AST/Expressions/Literals/AST_IntLiteral.h"
#include "AST/Expressions/Literals/AST_FloatLiteral.h"
#include "AST/Expressions/Literals/AST_StringLiteral.h"
#include "AST/Expressions/Literals/AST_NullptrLiteral.h"


UParser::UParser()
{
	UnaryPrefixOperatorMap = TMap<TSubclassOf<UT_Operator>, TSubclassOf<UAST_OneArgument> >();

	UnaryPrefixOperatorMap.Add(UT_Minus::StaticClass(), UAST_UnaryMinus::StaticClass());
	UnaryPrefixOperatorMap.Add(UT_Plus::StaticClass(), UAST_UnaryPlus::StaticClass());
	UnaryPrefixOperatorMap.Add(UT_MinusMinus::StaticClass(), UAST_DecrementPrefix::StaticClass());
	UnaryPrefixOperatorMap.Add(UT_PlusPlus::StaticClass(), UAST_IncrementPrefix::StaticClass());
	UnaryPrefixOperatorMap.Add(UT_Not::StaticClass(), UAST_Not::StaticClass());


	UnarySufixOperatorMap = TMap<TSubclassOf<UT_Operator>, TSubclassOf<UAST_OneArgument> >();

	UnarySufixOperatorMap.Add(UT_MinusMinus::StaticClass(), UAST_DecrementSufix::StaticClass());
	UnarySufixOperatorMap.Add(UT_PlusPlus::StaticClass(), UAST_IncrementSufix::StaticClass());
	

	BinaryOperatorMap = TMap<TSubclassOf<UT_Operator>, TSubclassOf<UAST_TwoArguments> >();

	BinaryOperatorMap.Add(UT_And::StaticClass(), UAST_And::StaticClass());
	BinaryOperatorMap.Add(UT_Plus::StaticClass(), UAST_Addition::StaticClass());
	BinaryOperatorMap.Add(UT_Divide::StaticClass(), UAST_Division::StaticClass());
	BinaryOperatorMap.Add(UT_EqualTo::StaticClass(), UAST_EqualTo::StaticClass());
	BinaryOperatorMap.Add(UT_Greater::StaticClass(), UAST_Greater::StaticClass());
	BinaryOperatorMap.Add(UT_GreaterOrEqual::StaticClass(), UAST_GreaterOrEqual::StaticClass());
	BinaryOperatorMap.Add(UT_Less::StaticClass(), UAST_Less::StaticClass());
	BinaryOperatorMap.Add(UT_LessOrEqual::StaticClass(), UAST_LessOrEqual::StaticClass());
	BinaryOperatorMap.Add(UT_Dot::StaticClass(), UAST_MemberAccess::StaticClass());
	BinaryOperatorMap.Add(UT_Modulo::StaticClass(), UAST_Modulo::StaticClass());
	BinaryOperatorMap.Add(UT_Multiply::StaticClass(), UAST_Multiplication::StaticClass());
	BinaryOperatorMap.Add(UT_NotEqualTo::StaticClass(), UAST_NotEqualTo::StaticClass());
	BinaryOperatorMap.Add(UT_Or::StaticClass(), UAST_Or::StaticClass());
	BinaryOperatorMap.Add(UT_Minus::StaticClass(), UAST_Subtraction::StaticClass());
	BinaryOperatorMap.Add(UT_Equal::StaticClass(), UAST_DirectAssignment::StaticClass());
	BinaryOperatorMap.Add(UT_DivideEqual::StaticClass(), UAST_DivideEqual::StaticClass());
	BinaryOperatorMap.Add(UT_MinusEqual::StaticClass(), UAST_MinusEqual::StaticClass());
	BinaryOperatorMap.Add(UT_ModuloEqual::StaticClass(), UAST_ModuloEqual::StaticClass());
	BinaryOperatorMap.Add(UT_MultiplyEqual::StaticClass(), UAST_MultiplyEqual::StaticClass());
	BinaryOperatorMap.Add(UT_PlusEqual::StaticClass(), UAST_PlusEqual::StaticClass());
}


// Helpers

bool UParser::IsIndexValid(int32 Index) const
{
	return TokenStream.IsValidIndex(Index);
}

UToken* UParser::GetTokenAtIndex(int32 Index) const
{
	if (!IsIndexValid(Index)) return nullptr;

	return TokenStream[Index];
}

bool UParser::IsTokenOfClassAtIndex(int32 Index, TSubclassOf<UToken> Class) const
{
	if (!GetTokenAtIndex(Index)) return false;

	return GetTokenAtIndex(Index)->GetClass()->IsChildOf(Class);
}

void UParser::ConsumeTokens(int32& Index, bool ConsumeWhitespace /*= true*/, bool ConsumeComment /*= true*/)
{
	while ((ConsumeWhitespace && IsTokenOfClassAtIndex(Index, UT_Whitespace::StaticClass())) 
			|| (ConsumeComment && IsTokenOfClassAtIndex(Index, UT_Comment::StaticClass())))
	{
		Index++;
	}
}

UToken* UParser::GetToken(int32& Index, bool ConsumeWhitespace /*= true*/, bool ConsumeComment /*= true*/, bool AutoIncrement /*= true*/)
{
	int32 tempIndex = Index;
	ConsumeTokens(tempIndex, ConsumeWhitespace, ConsumeComment);
	UToken* token = GetTokenAtIndex(tempIndex);
	if (token)
	{
		tempIndex++;
		if (AutoIncrement) Index = tempIndex;
	}

	return token;
}

bool UParser::IsTokenOfClass(int32& Index, TSubclassOf<UToken> Class, bool ConsumeWhitespace /*= true*/, bool ConsumeComment /*= true*/, bool AutoIncrement /*= true*/)
{
	int32 tempIndex = Index;
	ConsumeTokens(tempIndex, ConsumeWhitespace, ConsumeComment);
	bool result = IsTokenOfClassAtIndex(tempIndex, Class);
	if (result)
	{
		tempIndex++;
		if (AutoIncrement) Index = tempIndex;
	}

	return result;
}


/*======================
 Parse tokens
======================*/

TArray<UAST_Node*> UParser::ParseTokens(TArray<UToken*> Tokens)
{
	TokenStream = Tokens;
	int32 index = 0;
	TArray<UAST_Node*> result = TArray<UAST_Node*>();

	while (IsIndexValid(index))
	{
		// Optionaly consume semicolon
		if (IsTokenOfClass(index, UT_Semicolon::StaticClass())) continue;


		UAST_Node* temp = nullptr;

		// Class definition
		temp = ParseClassDefinition(index);
		if (temp)
		{
			result.Add(temp);
			continue;
		}

		// Function definition
		temp = ParseFunctionDefinition(index);
		if (temp)
		{
			result.Add(temp);
			continue;
		}

		// Parse rest
		temp = ParseNode(index);
		if (temp)
		{
			result.Add(temp);
			continue;
		}

		// Remove comments and whitespaces at the end of file
		int32 tempIndex = index;
		ConsumeTokens(index);
		// if tempIndex changed, then we consumed some tokens
		if (tempIndex != index) continue;


		// if we reach this point, there is an error
		ThrowError("Error");
		break;
	}

	return result;
}

/*======================
 Parse node
======================*/

UAST_Node* UParser::ParseNode(int32& Index)
{
	int32 CurrentIndex = Index;
	UAST_Node* CurrentNode = nullptr;

	// Variable definition
	CurrentNode = ParseVariableDefinition(CurrentIndex);
	if (CurrentNode)
	{
		Index = CurrentIndex;
		return CurrentNode;
	}

	// if
	CurrentNode = ParseIf(CurrentIndex);
	if (CurrentNode)
	{
		Index = CurrentIndex;
		return CurrentNode;
	}

	// while
	CurrentNode = ParseWhile(CurrentIndex);
	if (CurrentNode)
	{
		Index = CurrentIndex;
		return CurrentNode;
	}

	// for
	CurrentNode = ParseFor(CurrentIndex);
	if (CurrentNode)
	{
		Index = CurrentIndex;
		return CurrentNode;
	}

	// Do while
	CurrentNode = ParseDoWhile(CurrentIndex);
	if (CurrentNode)
	{
		Index = CurrentIndex;
		return CurrentNode;
	}

	// Scope
	CurrentNode = ParseScope(CurrentIndex);
	if (CurrentNode)
	{
		Index = CurrentIndex;
		return CurrentNode;
	}

	// return
	CurrentNode = ParseReturn(CurrentIndex);
	if (CurrentNode)
	{
		Index = CurrentIndex;
		return CurrentNode;
	}

	// break
	CurrentNode = ParseBreak(CurrentIndex);
	if (CurrentNode)
	{
		Index = CurrentIndex;
		return CurrentNode;
	}

	// continue
	CurrentNode = ParseContinue(CurrentIndex);
	if (CurrentNode)
	{
		Index = CurrentIndex;
		return CurrentNode;
	}

	// expression
	CurrentNode = ParseExpression(CurrentIndex);
	if (CurrentNode)
	{
		Index = CurrentIndex;
		return CurrentNode;
	}

	ConsumeTokens(CurrentIndex);
	if (IsIndexValid(CurrentIndex))
	{
		ThrowError("Unknown thingy.");
		return nullptr;
	}

	return nullptr;

}

/*======================
 Class definition
======================*/

UAST_ClassDefinition* UParser::ParseClassDefinition(int32& Index)
{
	int32 CurrentIndex = Index;

	// Class keyword
	if (!IsTokenOfClass(CurrentIndex, UT_Class::StaticClass())) return nullptr;

	// Construct ClassDefinition
	UAST_ClassDefinition* ClassDefinition = NewObject<UAST_ClassDefinition>(GetInterpreter());

	// Class name
	UToken* CurrentToken = GetToken(CurrentIndex);
	UT_Identifier* ClassIdentifierToken = Cast<UT_Identifier>(CurrentToken);
	if (!ClassIdentifierToken)
	{
		ThrowError(TEXT("Expected identifier after class keyword."));
		return nullptr;
	}
	ClassDefinition->Name = ClassIdentifierToken->ID;

	// Optional parent
	if (IsTokenOfClass(CurrentIndex, UT_Inherits::StaticClass()))
	{
		UT_Identifier* ParentNameToken = Cast<UT_Identifier>(GetToken(CurrentIndex));
		if (!ParentNameToken)
		{
			ThrowError(TEXT("Expected a parent after \"inherits\" keyword in class definition."));
			return nullptr;
		}
		ClassDefinition->ParentName = ParentNameToken->ID;
	}
	else ClassDefinition->ParentName = "class"; // inherit from base class

	// Open curly bracket
	if (!IsTokenOfClass(CurrentIndex, UT_OpenCurlyBracket::StaticClass()))
	{
		ThrowError(TEXT("Expected \"{\" after class identifier."));
		return nullptr;
	}

	// Parse all function and variable declarations
	while (!IsTokenOfClass(CurrentIndex, UT_ClosedCurlyBracket::StaticClass()))
	{
		UAST_FunctionDefinition* FunctionDefinition = ParseFunctionDefinition(CurrentIndex);

		if (FunctionDefinition)	ClassDefinition->FunctionDefinitions.Add(FunctionDefinition);
		else
		{
			UAST_VariableDefinition* VariableDefinition = ParseVariableDefinition(CurrentIndex);

			if (VariableDefinition)	ClassDefinition->VariableDefinitions.Add(VariableDefinition);
			else
			{
				// If this is not a function definition, variable definition or semicolon, then it's an error
				if (!IsTokenOfClass(CurrentIndex, UT_Semicolon::StaticClass()))
				{
					UToken* token = GetToken(CurrentIndex, true, true, false);
					ThrowError(TEXT("Unexpected token \"" + token->GetTokenName() + "\" found inside class definition. Expected either Function or variable definition."));
					return nullptr;
				}
			}
		}
	}

	// Finish
	Index = CurrentIndex;
	return ClassDefinition;
}

/*======================
 Function definition
======================*/

UAST_FunctionDefinition* UParser::ParseFunctionDefinition(int32& Index)
{
	int32 CurrentIndex = Index;

	// Function data
	FFunctionData data;

	// Check if it is a constructor
	if (IsTokenOfClass(CurrentIndex, UT_Constructor::StaticClass()))
	{
		data.ReturnType = "void";
		data.FunctionName = "constructor";
		data.ReturnsArray = false;
	}
	else
	{
		// Optional static
		data.IsStatic = IsTokenOfClass(CurrentIndex, UT_Static::StaticClass());

		// Identifier representing type
		FString type;
		bool isArray;
		if (!GetType(CurrentIndex, type, isArray))
		{
			return nullptr;
		}
		data.ReturnType = type;
		data.ReturnsArray = isArray;

		// Optional pass by reference return value
		data.IsReturnPassByReference = IsTokenOfClass(CurrentIndex, UT_Ampersand::StaticClass());

		// Get function name
		if (!GetFunctionName(CurrentIndex, data.FunctionName)) return nullptr;
	}

	// open round bracket
	if (!IsTokenOfClass(CurrentIndex, UT_OpenRoundBracket::StaticClass())) return nullptr;

	// Parameters
	TArray<FParameterData> Parameters;
	if (!GetParameters(CurrentIndex, Parameters))
	{
		ThrowError(TEXT("Invalid parameter in function definition."));
		return nullptr;
	}

	// Closed round bracket
	if (!IsTokenOfClass(CurrentIndex, UT_ClosedRoundBracket::StaticClass()))
	{
		ThrowError(TEXT("Missing \")\" in parameter list."));
		return nullptr;
	}

	// Optional const function
	data.IsConst = IsTokenOfClass(CurrentIndex, UT_Const::StaticClass());

	// Optional final
	data.IsFinal = IsTokenOfClass(CurrentIndex, UT_Final::StaticClass());

	// Construct function definition;
	UAST_FunctionDefinition* FunctionDefinition = NewObject<UAST_FunctionDefinition>(GetInterpreter());
	FunctionDefinition->FunctionData = data;
	FunctionDefinition->FunctionData.ParameterData = Parameters;

	// Function body
	UAST_Scope* FunctionBody = ParseScope(CurrentIndex);
	if (FunctionBody) FunctionDefinition->Scope = FunctionBody;
	else
	{
		ThrowError(TEXT("Invalid function body"));
		return nullptr;
	}

	// Finish
	Index = CurrentIndex;
	return FunctionDefinition;
}

/*======================
 Variable definition
======================*/

UAST_VariableDefinition* UParser::ParseVariableDefinition(int32& Index)
{
	int32 CurrentIndex = Index;

	// Optional static
	bool IsStatic = IsTokenOfClass(CurrentIndex, UT_Static::StaticClass());

	// Identifier representing type
	FString type;
	bool isArray;
	if (!GetType(CurrentIndex, type, isArray))
	{
		return nullptr;
	}

	// Identifier representing name
	UT_Identifier* Identifier = Cast<UT_Identifier>(GetToken(CurrentIndex));

	if (!Identifier) return nullptr;
	FString Name = Identifier->ID;

	//Construct Variable definition
	UAST_VariableDefinition* VariableDefinition = NewObject<UAST_VariableDefinition>(GetInterpreter());
	VariableDefinition->Type = type;
	VariableDefinition->IsArray = isArray;
	VariableDefinition->Name = Name;
	VariableDefinition->IsStatic = IsStatic;

	// Optional initialization
	if (IsTokenOfClass(CurrentIndex, UT_Equal::StaticClass()))
	{
		UAST_Expression* Initialization = ParseExpression(CurrentIndex);
		if (Initialization) VariableDefinition->InitExpression = Initialization;
		else 
		{
			ThrowError(TEXT("Invalid initialization for variable definition"));
			return nullptr;
		}
	}

	// Finish
	Index = CurrentIndex;
	return VariableDefinition;

}

/*======================
 Function call
======================*/

UAST_FunctionCall* UParser::ParseFunctionCall(int32& Index)
{
	int32 CurrentIndex = Index;

	// Identifier representing name
	UT_Identifier* NameIdentifier = Cast<UT_Identifier>(GetToken(CurrentIndex));
	if (!NameIdentifier) return nullptr;

	// Open round bracket
	if (!IsTokenOfClass(CurrentIndex, UT_OpenRoundBracket::StaticClass())) return nullptr;

	// Construct Function call
	UAST_FunctionCall* FunctionCall = NewObject<UAST_FunctionCall>(GetInterpreter());
	FunctionCall->FunctionName = NameIdentifier->ID;

	// Arguments
	TArray<UAST_Expression*> Arguments;

	while (!IsTokenOfClass(CurrentIndex, UT_ClosedRoundBracket::StaticClass(), true, true, false))
	{
		if (Arguments.Num() > 0 && !IsTokenOfClass(CurrentIndex, UT_Comma::StaticClass()))
		{
			ThrowError(TEXT("Expected a \",\" after an argument"));
			return nullptr;
		}

		UAST_Expression* arg = ParseExpression(CurrentIndex);
		if (arg) Arguments.Add(arg);
		else
		{
			ThrowError(TEXT("Invalid argument"));
			return nullptr;
		}
	}

	// Closed round bracket
	if (!IsTokenOfClass(CurrentIndex, UT_ClosedRoundBracket::StaticClass()))
	{
		ThrowError(TEXT("Expected a closing bracket in function call argument list"));
		return nullptr;
	}

	// Add arguments to function call
	FunctionCall->Arguments = Arguments;

	// Finish
	Index = CurrentIndex;
	return FunctionCall;

}

/*======================
 Variable call
======================*/

UAST_VariableCall* UParser::ParseVariableCall(int32& Index)
{
	int32 CurrentIndex = Index;

	// Get name
	UT_Identifier* Name = Cast<UT_Identifier>(GetToken(CurrentIndex));
	if (!Name) return nullptr;

	// Construct variable call
	UAST_VariableCall* VariableCall = NewObject<UAST_VariableCall>(GetInterpreter());
	VariableCall->VariableName = Name->ID;

	// Finish
	Index = CurrentIndex;
	return VariableCall;
}

/*======================
 If
======================*/

UAST_If* UParser::ParseIf(int32& Index)
{
	int32 CurrentIndex = Index;

	// If
	if (!IsTokenOfClass(CurrentIndex, UT_If::StaticClass())) return nullptr;

	// Open bracket
	if (!IsTokenOfClass(CurrentIndex, UT_OpenRoundBracket::StaticClass()))
	{
		ThrowError(TEXT("Expected \"(\" after if."));
		return nullptr;
	}

	// Condition
	UAST_Expression* Condition = ParseExpression(CurrentIndex);
	if (!Condition)
	{
		ThrowError(TEXT("Invalid expression"));
		return nullptr;
	}

	// Closed bracket
	if (!IsTokenOfClass(CurrentIndex, UT_ClosedRoundBracket::StaticClass()))
	{
		ThrowError(TEXT("Expected \")\" after condition in if."));
		return nullptr;
	}

	// Construct if
	UAST_If* If = NewObject<UAST_If>(GetInterpreter());
	If->Condition = Condition;

	// True branch
	UAST_Node* Node = ParseNode(CurrentIndex);
	if (!Node)
	{
		ThrowError(TEXT("Invalid if (True branch)."));
		return nullptr;
	}
	If->TrueBranch = Node;

	// Optional false branch
	if (IsTokenOfClass(CurrentIndex, UT_Else::StaticClass()))
	{
		Node = ParseNode(CurrentIndex);
		if (!Node)
		{
			ThrowError(TEXT("Invalid if (False branch)."));
			return nullptr;
		}
		If->FalseBranch = Node;
	}

	// Finish
	Index = CurrentIndex;
	return If;
}

/*======================
 For
======================*/

UAST_For* UParser::ParseFor(int32& Index)
{
	int32 CurrentIndex = Index;

	// For keyword
	if (!IsTokenOfClass(CurrentIndex, UT_For::StaticClass())) return nullptr;

	// Open round bracket
	if (!IsTokenOfClass(CurrentIndex, UT_OpenRoundBracket::StaticClass()))
	{
		ThrowError(TEXT("Expected \"(\" after for."));
		return nullptr;
	}

	// Construct for
	UAST_For* For = NewObject<UAST_For>(GetInterpreter());

	// Initialization
	UAST_VariableDefinition* Initialization = ParseVariableDefinition(CurrentIndex);
	if (!Initialization)
	{
		ThrowError(TEXT("invalid variable declaration inside for."));
		return nullptr;
	}
	For->Initialization = Initialization;

	// Semicolon
	if (!IsTokenOfClass(CurrentIndex, UT_Semicolon::StaticClass()))
	{
		ThrowError(TEXT("Exprected \";\" after variable declaration within for."));
		return nullptr;
	}

	// Condition
	UAST_Expression* Condition = ParseExpression(CurrentIndex);
	if (!Condition)
	{
		ThrowError(TEXT("invalid condition inside for"));
		return nullptr;
	}
	For->Condition = Condition;

	// Semicolon
	if (!IsTokenOfClass(CurrentIndex, UT_Semicolon::StaticClass()))
	{
		ThrowError(TEXT("Exprected \";\" after condition within for."));
		return nullptr;
	}

	// Update
	UAST_Expression* Update = ParseExpression(CurrentIndex);
	if (!Update)
	{
		ThrowError(TEXT("Invalid update in for header."));
		return nullptr;
	}
	For->Update = Update;

	// Closed round bracket
	if (!IsTokenOfClass(CurrentIndex, UT_ClosedRoundBracket::StaticClass()))
	{
		ThrowError(TEXT("Expected \")\" in for header."));
		return nullptr;
	}

	// Body
	UAST_Node* Body = ParseNode(CurrentIndex);
	if (!Body)
	{
		ThrowError(TEXT("Invalid for body."));
		return nullptr;
	}
	For->Body = Body;

	// Finish
	Index = CurrentIndex;
	return For;
}

/*======================
 While
======================*/

UAST_While* UParser::ParseWhile(int32& Index)
{
	int32 CurrentIndex = Index;

	// While keyword
	if (!IsTokenOfClass(CurrentIndex, UT_While::StaticClass())) return nullptr;

	// Open round bracket
	if (!IsTokenOfClass(CurrentIndex, UT_OpenRoundBracket::StaticClass()))
	{
		ThrowError(TEXT("Expected \"(\" after while keyword"));
		return nullptr;
	}

	// Construct while
	UAST_While* While = NewObject<UAST_While>(GetInterpreter());

	// Condition
	UAST_Expression* Condition = ParseExpression(CurrentIndex);
	if (!Condition)
	{
		ThrowError(TEXT("invalid condition inside while."));
		return nullptr;
	}
	While->Condition = Condition;

	// Closed round bracket
	if (!IsTokenOfClass(CurrentIndex, UT_ClosedRoundBracket::StaticClass()))
	{
		ThrowError(TEXT("Unclosed bracket in while condition."));
		return nullptr;
	}

	// Body
	UAST_Node* Body = ParseNode(CurrentIndex);
	if (!Body)
	{
		ThrowError(TEXT("Invalid body in a ehile statement."));
		return nullptr;
	}
	While->Body = Body;

	//Finish
	Index = CurrentIndex;
	return While;
}

/*======================
 Do while
======================*/

UAST_DoWhile* UParser::ParseDoWhile(int32& Index)
{
	int32 CurrentIndex = Index;

	// Do keyword
	if (!IsTokenOfClass(CurrentIndex, UT_Do::StaticClass())) return nullptr;

	// Construct Do while
	UAST_DoWhile* DoWhile = NewObject<UAST_DoWhile>(GetInterpreter());

	// Body
	UAST_Node* Body = ParseNode(CurrentIndex);
	if (!Body)
	{
		ThrowError(TEXT("Invalid body in do while"));
		return nullptr;
	}
	DoWhile->Body = Body;

	// While keyword
	if (!IsTokenOfClass(CurrentIndex, UT_While::StaticClass()))
	{
		ThrowError(TEXT("While keyword missing from \"do while\" loop."));
		return nullptr;
	}

	// Open round bracket
	if (!IsTokenOfClass(CurrentIndex, UT_OpenRoundBracket::StaticClass()))
	{
		ThrowError(TEXT("\"(\" missin from \"do while\" loop."));
		return nullptr;
	}

	// Condition
	UAST_Expression* Condition = ParseExpression(CurrentIndex);
	if (!Condition)
	{
		ThrowError(TEXT("Invalid condition in \"do while\" loop."));
		return nullptr;
	}
	DoWhile->Condition = Condition;

	// Closed round bracket
	if (!IsTokenOfClass(CurrentIndex, UT_ClosedRoundBracket::StaticClass()))
	{
		ThrowError(TEXT("Missing \")\" from condition in \"do while\" loop."));
		return nullptr;
	}

	// Finish
	Index = CurrentIndex;
	return DoWhile;
}

/*======================
 Scope
======================*/

UAST_Scope* UParser::ParseScope(int32& Index)
{
	int32 CurrentIndex = Index;

	// Open curly bracket
	if (!IsTokenOfClass(CurrentIndex, UT_OpenCurlyBracket::StaticClass())) return nullptr;

	// Construct scope
	UAST_Scope* Scope = NewObject<UAST_Scope>(GetInterpreter());

	// Scope content
	while (!IsTokenOfClass(CurrentIndex, UT_ClosedCurlyBracket::StaticClass(), true, true, false))
	{
		// Optionaly consume semicolon
		if (IsTokenOfClass(CurrentIndex, UT_Semicolon::StaticClass())) continue;
		
		UAST_Node* Node = ParseNode(CurrentIndex);
		if (!Node)
		{
			ThrowError(TEXT("invalid scope content."));
			return nullptr;
		}

		Scope->Children.Add(Node);
	}

	// Closed curly bracket
	if (!IsTokenOfClass(CurrentIndex, UT_ClosedCurlyBracket::StaticClass()))
	{
		ThrowError(TEXT("Missing \"{\" from scope."));
		return nullptr;
	}

	// Finish
	Index = CurrentIndex;
	return Scope;
}

/*======================
 Return
======================*/

UAST_Return* UParser::ParseReturn(int32& Index)
{
	int32 CurrentIndex = Index;

	// Return keyword
	if (!IsTokenOfClass(CurrentIndex, UT_Return::StaticClass())) return nullptr;

	// Construct return
	UAST_Return* Return = NewObject<UAST_Return>(GetInterpreter());

	// Optional return expression
	UAST_Expression* ReturnExpression = ParseExpression(CurrentIndex);
	if (ReturnExpression) Return->ReturnExpression = ReturnExpression;

	// Finish
	Index = CurrentIndex;
	return Return;
}

/*======================
 Break
======================*/

UAST_Break* UParser::ParseBreak(int32& Index)
{
	int32 CurrentIndex = Index;
	if (!IsTokenOfClass(CurrentIndex, UT_Break::StaticClass())) return nullptr;

	Index = CurrentIndex;
	return NewObject<UAST_Break>(GetInterpreter());
}

/*======================
 Continue
======================*/

UAST_Continue* UParser::ParseContinue(int32& Index)
{
	int32 CurrentIndex = Index;
	if (!IsTokenOfClass(CurrentIndex, UT_Continue::StaticClass())) return nullptr;

	Index = CurrentIndex;
	return NewObject<UAST_Continue>(GetInterpreter());
}

/*======================
 Expression
======================*/

UAST_Expression* UParser::ParseExpression(int32& Index)
{
	int32 CurrentIndex = Index;

	UAST_Expression* Tree = RPNtoAST(GetRPN(CurrentIndex));
	if (!Tree) return nullptr;

	Index = CurrentIndex;
	return Tree;
}

// Parse helpers

bool UParser::GetParameters(int32& Index, TArray<FParameterData>& Parameters)
{
	int32 CurrentIndex = Index;
	do
	{
		FParameterData CurrentParameter;

		// Optional const
		CurrentParameter.IsConst = IsTokenOfClass(CurrentIndex, UT_Const::StaticClass());

		// Parameter type
		FString type;
		bool IsArray;
		if (GetType(CurrentIndex, type, IsArray))
		{
			CurrentParameter.Type = type;
			CurrentParameter.IsArray = IsArray;
		}
		else
		{
			// No parameters
			if (Parameters.Num() <= 0) return true;

			ThrowError(TEXT("Expected a type as part of function definition parameter."));
			return false;
		}

		// Optional pass by reference
		CurrentParameter.IsPassByReference = IsTokenOfClass(CurrentIndex, UT_Ampersand::StaticClass());

		// Parameter name
		UT_Identifier* Identifier = Cast<UT_Identifier>(GetToken(CurrentIndex));
		if (Identifier) CurrentParameter.Name = Identifier->ID;
		else
		{
			ThrowError(TEXT("Expected a name as part of function definition parameter."));
			return false;
		}

		Parameters.Add(CurrentParameter);
	} while (IsTokenOfClass(CurrentIndex, UT_Comma::StaticClass()));

	Index = CurrentIndex;
	return true;
}

bool UParser::GetFunctionName(int32& Index, FString& Name)
{
	int32 CurrentIndex = Index;

	// Operator
	if (IsTokenOfClass(CurrentIndex, UT_OperatorKeyword::StaticClass()))
	{
		// Next token must be an operator
		UT_Operator* operatorToken = Cast<UT_Operator>(GetToken(CurrentIndex));
		if (!operatorToken)
		{
			ThrowError("Expected an operator after \"operator\" keyword.");
			return false;
		}
		Name = "operator " + operatorToken->GetTokenName();
		Index = CurrentIndex;
		return true;
	}

	// Conversion
	if (IsTokenOfClass(CurrentIndex, UT_Convert::StaticClass()))
	{
		Name = "convert";
		// optional auto
		if (IsTokenOfClass(CurrentIndex, UT_Auto::StaticClass()))
			Name += " auto";
		// Type
		UT_Identifier* Identifier = Cast<UT_Identifier>(GetToken(CurrentIndex));
		if (!Identifier)
		{
			ThrowError("Expected an identifier in converion function.");
			return false;
		}
		Name += " " + Identifier->ID;
		Index = CurrentIndex;
		return true;
	}

	// Get function name from identifier
	UT_Identifier* Identifier = Cast<UT_Identifier>(GetToken(CurrentIndex));
	if (!Identifier) return false;
	Name = Identifier->ID;
	Index = CurrentIndex;
	return true;
}

// Expression helpers

UAST_Literal* UParser::ParseLiteral(int32& Index)
{
	int32 CurrentIndex = Index;

	// Check if the token is a literal, to avoid unecessary casting
	UToken* Temp = GetToken(CurrentIndex);
	if (!Temp || !Temp->GetClass()->IsChildOf(UT_Literal::StaticClass())) return nullptr;

	// Bool
	UT_BoolLiteral* BoolToken = Cast<UT_BoolLiteral>(Temp);
	if (BoolToken)
	{
		UAST_BoolLiteral* Bool = NewObject<UAST_BoolLiteral>(GetInterpreter());
		Bool->Value = BoolToken->Value;
		Index = CurrentIndex;
		return Bool;
	}

	// Int
	UT_IntLiteral* IntToken = Cast<UT_IntLiteral>(Temp);
	if (IntToken)
	{
		UAST_IntLiteral* Int = NewObject<UAST_IntLiteral>(GetInterpreter());
		Int->Value = IntToken->Value;
		Index = CurrentIndex;
		return Int;
	}

	// Float
	UT_FloatLiteral* FloatToken = Cast<UT_FloatLiteral>(Temp);
	if (FloatToken)
	{
		UAST_FloatLiteral* Float = NewObject<UAST_FloatLiteral>(GetInterpreter());
		Float->Value = FloatToken->Value;
		Index = CurrentIndex;
		return Float;
	}

	// String
	UT_StringLiteral* StringToken = Cast<UT_StringLiteral>(Temp);
	if (StringToken)
	{
		UAST_StringLiteral* String = NewObject<UAST_StringLiteral>(GetInterpreter());
		String->Value = StringToken->Value;
		Index = CurrentIndex;
		return String;
	}

	// Nullptr literal
	if (Temp->IsA<UT_Nullptr>())
	{
		UAST_NullptrLiteral* Nullptr = NewObject<UAST_NullptrLiteral>(GetInterpreter());
		Index = CurrentIndex;
		return Nullptr;
	}

	ThrowError(TEXT("Found a literal that is neither a bool, int, float or string. There is either a bug, or fabric of reality is compromised. Either way, God help us."));
	return nullptr;
}

UAST_Expression* UParser::ParseOperand(int32& Index)
{
	int32 CurrentIndex = Index;
	UAST_Expression* Operand = nullptr;

	// Literal
	Operand = ParseLiteral(CurrentIndex);
	if (Operand)
	{
		Index = CurrentIndex;
		return Operand;
	}

	// Array get
	Operand = ParseArrayGet(CurrentIndex);
	if (Operand)
	{
		Index = CurrentIndex;
		return Operand;
	}

	// Function call
	Operand = ParseFunctionCall(CurrentIndex);
	if (Operand)
	{
		Index = CurrentIndex;
		return Operand;
	}

	// Variable call
	Operand = ParseVariableCall(CurrentIndex);
	if (Operand)
	{
		Index = CurrentIndex;
		return Operand;
	}

	return nullptr;
}

TArray<UAST_Expression*> UParser::GetRPN(int32& Index)
{
	int32 CurrentIndex = Index;

	TArray<UAST_Expression*> OutputQueue = TArray<UAST_Expression*>();
	TArray<UAST_Operator*> OperatorStack = TArray<UAST_Operator*>();

	while (true)
	{
		// Unary prefix
		while (true)
		{
			UAST_OneArgument* UnaryPrefix = GetUnaryPrefixOperator(CurrentIndex);
			if (!UnaryPrefix) break;
			AddOperator(UnaryPrefix, OutputQueue, OperatorStack);
		}

		// brackets
		if (IsTokenOfClass(CurrentIndex, UT_OpenRoundBracket::StaticClass()))
		{
			UAST_Expression* Expression = ParseExpression(CurrentIndex);
			if (!Expression)
			{
				ThrowError("Invalid expression after \"(\".");
				return TArray<UAST_Expression*>();
			}
			if (!IsTokenOfClass(CurrentIndex, UT_ClosedRoundBracket::StaticClass()))
			{
				ThrowError("Missing \")\".");
				return TArray<UAST_Expression*>();
			}
			OutputQueue.Add(Expression);
		}
		else
		{
			// Operand
			UAST_Expression* Operand = ParseOperand(CurrentIndex);
			if (!Operand)
			{
				if (OutputQueue.Num() > 0 || OperatorStack.Num() > 0)
					ThrowError(TEXT("Invalid expression. Expected an operand."));

				return TArray<UAST_Expression*>();
			}
			OutputQueue.Add(Operand);
		}

		// Unary sufix
		while (true)
		{
			UAST_OneArgument* UnarySufix = GetUnarySufixOperator(CurrentIndex);
			if (!UnarySufix) break;
			AddOperator(UnarySufix, OutputQueue, OperatorStack);
		}


		// Binary operator
		UAST_TwoArguments* BinaryOperator = GetBinaryOperator(CurrentIndex);
		if (!BinaryOperator) break;
		AddOperator(BinaryOperator, OutputQueue, OperatorStack);
	}

	while (OperatorStack.Num() > 0)
	{
		UAST_Operator* TopOperator = OperatorStack.Last();
		OperatorStack.RemoveAt(OperatorStack.Num() - 1);
		OutputQueue.Add(TopOperator);
	}

	Index = CurrentIndex;
	return OutputQueue;

}

UAST_OneArgument* UParser::GetUnaryPrefixOperator(int32& Index)
{
	int32 CurrentIndex = Index;

	UT_Operator* OperatorToken = Cast<UT_Operator>(GetToken(CurrentIndex));

	if (!OperatorToken) return nullptr;
	if (!UnaryPrefixOperatorMap.Contains(OperatorToken->GetClass())) return nullptr;

	Index = CurrentIndex;
	TSubclassOf<UAST_OneArgument> OperatorClass = UnaryPrefixOperatorMap[OperatorToken->GetClass()];
	return NewObject<UAST_OneArgument>(GetInterpreter(), OperatorClass);
}

UAST_OneArgument* UParser::GetUnarySufixOperator(int32& Index)
{
	int32 CurrentIndex = Index;

	UT_Operator* OperatorToken = Cast<UT_Operator>(GetToken(CurrentIndex));

	if (!OperatorToken) return nullptr;
	if (!UnarySufixOperatorMap.Contains(OperatorToken->GetClass())) return nullptr;

	Index = CurrentIndex;
	TSubclassOf<UAST_OneArgument> OperatorClass = UnarySufixOperatorMap[OperatorToken->GetClass()];
	return NewObject<UAST_OneArgument>(GetInterpreter(), OperatorClass);
}

UAST_TwoArguments* UParser::GetBinaryOperator(int32& Index)
{
	int32 CurrentIndex = Index;
	UT_Operator* OperatorToken = Cast<UT_Operator>(GetToken(CurrentIndex));

	if (!OperatorToken) return nullptr;
	if (!BinaryOperatorMap.Contains(OperatorToken->GetClass())) return nullptr;

	Index = CurrentIndex;
	TSubclassOf<UAST_TwoArguments> OperatorClass = BinaryOperatorMap[OperatorToken->GetClass()];
	return NewObject<UAST_TwoArguments>(GetInterpreter(), OperatorClass);
}

void UParser::AddOperator(UAST_Operator* OperatorToAdd, TArray<UAST_Expression*>& OutputQueue, TArray<UAST_Operator*>& OperatorStack)
{
	if (!OperatorToAdd) return;

	while (OperatorStack.Num() > 0 && (OperatorStack.Last()->GetPrecedence() < OperatorToAdd->GetPrecedence() ||
		(OperatorStack.Last()->GetPrecedence() == OperatorToAdd->GetPrecedence() &&
			OperatorStack.Last()->GetAssociativity() == EOperatorAssociativity::LeftToRight)))
	{
		UAST_Operator* TopOperator = OperatorStack.Last();
		OperatorStack.RemoveAt(OperatorStack.Num() - 1);
		OutputQueue.Add(TopOperator);
	}
	OperatorStack.Add(OperatorToAdd);
}


UAST_Expression* UParser::RPNtoAST(TArray<UAST_Expression*> RPN)
{
	if (RPN.Num() <= 0) return nullptr;

	for (int32 CurrentIndex = 0; CurrentIndex < RPN.Num(); CurrentIndex++)
	{
		// Find an operator
		UAST_Operator* CurrentOperator = Cast<UAST_Operator>(RPN[CurrentIndex]);
		if (!CurrentOperator) continue;

		if (!CurrentOperator->HasAllArguments())
		{
			// Go back by the number of arguments
			CurrentIndex -= CurrentOperator->GetNumberOfArguments();
			if (CurrentIndex < 0)
			{
				ThrowError(TEXT("Invalid RPN."));
				return nullptr;
			}

			for (int i = 0; i < CurrentOperator->GetNumberOfArguments(); ++i)
			{
				CurrentOperator->AddArgument(RPN[CurrentIndex]);
				RPN.RemoveAt(CurrentIndex);
			}
		}

	}

	if (RPN.Num() != 1)
	{
		ThrowError(TEXT("invalid number of operands in RPN."));
		return nullptr;
	}

	return RPN[0];
}


bool UParser::GetType(int32& Index, FString& type, bool& IsArray)
{
	int32 currentIndex = Index;
	if (IsTokenOfClass(currentIndex, UT_Array::StaticClass()))
	{
		if (!IsTokenOfClass(currentIndex, UT_Less::StaticClass()))
		{
			ThrowError("Expected a < after array keyword.");
			return false;
		}

		UT_Identifier* id = Cast<UT_Identifier>(GetToken(currentIndex));
		if (!id)
		{
			ThrowError("Expected a type after array<.");
			return false;
		}

		if (!IsTokenOfClass(currentIndex, UT_Greater::StaticClass()))
		{
			ThrowError("Expected a > after \"array<" + id->ID + "\".");
			return false;
		}
		Index = currentIndex;
		type = id->ID;
		IsArray = true;
		return true;
	}

	UT_Identifier* id = Cast<UT_Identifier>(GetToken(currentIndex));
	if (!id)
	{
		return false;
	}

	Index = currentIndex;
	type = id->ID;
	IsArray = false;
	return true;
}

UAST_MemberAccess* UParser::ParseArrayGet(int32& Index)
{
	int32 CurrentIndex = Index;

	UAST_VariableCall* varCall = ParseVariableCall(CurrentIndex);
	if (!varCall) return nullptr;

	if (!IsTokenOfClass(CurrentIndex, UT_OpenSquareBracket::StaticClass())) return nullptr;

	UAST_Expression* indexExpression = ParseExpression(CurrentIndex);
	if (!indexExpression)
	{
		ThrowError("Expected an expression after [.");
		return nullptr;
	}

	if (!IsTokenOfClass(CurrentIndex, UT_ClosedSquareBracket::StaticClass()))
	{
		ThrowError("Expected ] after [ <expression>.");
		return nullptr;
	}

	// Create member access with function data and variable
	UAST_FunctionCall* getFunction = NewObject<UAST_FunctionCall>(GetInterpreter());
	getFunction->Arguments.Add(indexExpression);
	getFunction->FunctionName = "get";
	UAST_MemberAccess* memberAccess = NewObject<UAST_MemberAccess>(GetInterpreter());
	memberAccess->lhs = varCall;
	memberAccess->rhs = getFunction;
	Index = CurrentIndex;

	return memberAccess;
}


