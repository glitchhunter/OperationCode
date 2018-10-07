// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Interpreter/InterpreterComponent.h"
#include "Parser.generated.h"

class UToken;

class UAST_Node;
class UAST_ClassDefinition;
class UAST_FunctionDefinition;
class UAST_VariableDefinition;

class UAST_FunctionCall;
class UAST_VariableCall;

class UAST_If;
class UAST_For;
class UAST_While;
class UAST_DoWhile;

class UAST_Return;
class UAST_Scope;
class UAST_Expression;
class UAST_Operator;
class UAST_OneArgument;
class UAST_TwoArguments;
class UAST_Break;
class UAST_Continue;

class UAST_MemberAccess;
class UT_Operator;
class UAST_Literal;


struct FParameterData;

/**
 * 
 */
UCLASS(Blueprintable)
class OPERATIONCODE_API UParser : public UInterpreterComponent
{
	GENERATED_BODY()
	
public:

	UParser();

	// Helpers

	bool IsIndexValid(int32 Index) const;

	UToken* GetTokenAtIndex(int32 Index) const;

	bool IsTokenOfClassAtIndex(int32 Index, TSubclassOf<UToken> Class) const;
	
	void ConsumeTokens(int32& Index, bool ConsumeWhitespace = true, bool ConsumeComment = true);

	UToken* GetToken(int32& Index, bool ConsumeWhitespace = true, bool ConsumeComment = true, bool AutoIncrement = true);

	bool IsTokenOfClass(int32& Index, TSubclassOf<UToken> Class, bool ConsumeWhitespace = true, bool ConsumeComment = true, bool AutoIncrement = true);


	// Parser functions

	UFUNCTION(BlueprintCallable)
	TArray<UAST_Node*> ParseTokens(TArray<UToken*> Tokens);

	UAST_Node* ParseNode(int32& Index);

	UAST_ClassDefinition* ParseClassDefinition(int32& Index);

	UAST_FunctionDefinition* ParseFunctionDefinition(int32& Index);

	UAST_VariableDefinition* ParseVariableDefinition(int32& Index);

	UAST_FunctionCall* ParseFunctionCall(int32& Index);

	UAST_VariableCall* ParseVariableCall(int32& Index);

	UAST_If* ParseIf(int32& Index);

	UAST_For* ParseFor(int32& Index);

	UAST_While* ParseWhile(int32& Index);

	UAST_DoWhile* ParseDoWhile(int32& Index);

	UAST_Scope* ParseScope(int32& Index);

	UAST_Return* ParseReturn(int32& Index);

	UAST_Break* ParseBreak(int32& Index);

	UAST_Continue* ParseContinue(int32& Index);

	UAST_Expression* ParseExpression(int32& Index);

	// Parse helpers

	bool GetParameters(int32& Index, TArray<FParameterData>& Parameters);

	bool GetFunctionName(int32& Index, FString& Name);



	UAST_Literal* ParseLiteral(int32& Index);

	UAST_Expression* ParseOperand(int32& Index);

	TArray<UAST_Expression*> GetRPN(int32& Index);

	UAST_OneArgument* GetUnaryPrefixOperator(int32& Index);

	UAST_OneArgument* GetUnarySufixOperator(int32& Index);

	UAST_TwoArguments* GetBinaryOperator(int32& Index);

	void AddOperator(UAST_Operator* OperatorToAdd, TArray<UAST_Expression*>& OutputQueue, TArray<UAST_Operator*>& OperatorStack);

	UAST_Expression* RPNtoAST(TArray<UAST_Expression*> RPN);

	UAST_MemberAccess* ParseArrayGet(int32& Index);


private:

	TArray<UToken*> TokenStream;
	
	TMap<TSubclassOf<UT_Operator>, TSubclassOf<UAST_OneArgument> > UnaryPrefixOperatorMap;

	TMap<TSubclassOf<UT_Operator>, TSubclassOf<UAST_OneArgument> > UnarySufixOperatorMap;

	TMap<TSubclassOf<UT_Operator>, TSubclassOf<UAST_TwoArguments> > BinaryOperatorMap;

	bool GetType(int32& Index, FString& type, bool& IsArray);

	
	
};
