// Fill out your copyright notice in the Description page of Project Settings.

#include "SAP_Literal.h"
#include "Interpreter/SemanticAnalysis/SymbolTable.h"





void USAP_Literal::Analyse(UAST_Basic* Basic)
{
	AnalyseChildren(Basic);
}

void USAP_Literal::Analyse(UAST_Main* Main)
{
	if (GetSymbolTable()->TopOwner)
	{
		UAST_ClassDefinition** topClass = GetSymbolTable()->ClassNames.Find(GetSymbolTable()->TopOwner->Type);
		if (topClass) Owner = *topClass;
		else Owner = nullptr;
	}
	else Owner = nullptr;

	AnalyseChildren(Main);
}

void USAP_Literal::Analyse(UAST_ClassDefinition* ClassDefinition)
{
	Owner = ClassDefinition;

	for (UAST_FunctionDefinition* currentFunction : ClassDefinition->FunctionDefinitions)
		currentFunction->Analyse(this);

	if (GetSymbolTable()->TopOwner)
	{
		UAST_ClassDefinition** topClass = GetSymbolTable()->ClassNames.Find(GetSymbolTable()->TopOwner->Type);
		if (topClass) Owner = *topClass;
		else Owner = nullptr;
	}
	else Owner = nullptr;
}

void USAP_Literal::Analyse(UAST_FunctionDefinition* FunctionDefinition)
{
	if (!FunctionDefinition->Scope) return;

	FunctionDefinition->Scope->Analyse(this);
}

void USAP_Literal::Analyse(UAST_VariableDefinition* VariableDefinition)
{
	if (!VariableDefinition->InitExpression) return;

	VariableDefinition->InitExpression->Analyse(this);
}

void USAP_Literal::Analyse(UAST_DoWhile* DoWhile)
{
	AnalyseChildren(DoWhile);
}

void USAP_Literal::Analyse(UAST_For* For)
{
	AnalyseChildren(For);
}

void USAP_Literal::Analyse(UAST_If* If)
{
	AnalyseChildren(If);
}

void USAP_Literal::Analyse(UAST_While* While)
{
	AnalyseChildren(While);
}

void USAP_Literal::Analyse(UAST_FunctionCall* FunctionCall)
{
	UAST_FunctionDefinition* definition;
	UAST_ClassDefinition* previousCaller = Caller;

	// special case for constructors
	UAST_ClassDefinition** constructorClass = GetSymbolTable()->ClassNames.Find(FunctionCall->FunctionName);
	if (constructorClass)
	{
		TArray<UAST_FunctionDefinition*> DefinitionArrays = GetSymbolTable()->GetFunctionDefinitions(FunctionCall, *constructorClass, ElementType, true);
		// Default constructor
		if (DefinitionArrays.Num() == 0) return;
		else definition = DefinitionArrays[0];
	}
	else
	{
		UAST_ClassDefinition* owningClass = Caller ? Caller : Owner;
		TArray<UAST_FunctionDefinition*> funDefinitions = GetSymbolTable()->GetFunctionDefinitions(FunctionCall, owningClass, ElementType, true);
		// if no definitions found with this owner, try as static function
		if (funDefinitions.Num() == 0) definition = GetSymbolTable()->GetFunctionDefinitions(FunctionCall, nullptr, ElementType, true)[0];
		else definition = funDefinitions[0];
	}

	Caller = nullptr;

	for (int i = 0; i < FunctionCall->Arguments.Num(); ++i)
	{
		IsLiteral = false;
		FunctionCall->Arguments[i]->Analyse(this);

		if (IsLiteral && definition->FunctionData.ParameterData[i].IsPassByReference && !definition->FunctionData.ParameterData[i].IsConst)
		{
			ThrowError("Cannot pass a literal by reference unless it's a const argument. In function "
				+ definition->FunctionData.FunctionName + ".");
		}
	}
	Caller = previousCaller;
	IsLiteral = false;
}

void USAP_Literal::Analyse(UAST_TwoArguments* TwoArguments)
{
	FString name = "operator " + TwoArguments->GetDescription();
	FExpressionReturn* lhsReturn = GetSymbolTable()->ExpressionReturns.Find(TwoArguments->lhs);
	FExpressionReturn* rhsReturn = GetSymbolTable()->ExpressionReturns.Find(TwoArguments->rhs);

	TArray<FParamSignature> paramSig;
	paramSig.Add(FParamSignature(lhsReturn->ReturnType, lhsReturn->ReturnsArray()));
	paramSig.Add(FParamSignature(rhsReturn->ReturnType, rhsReturn->ReturnsArray()));

	// Get definition
	UAST_FunctionDefinition* Definition = GetSymbolTable()->GetOverloadedOperator(FFunctionSignature(name, paramSig));


	IsLiteral = false;
	TwoArguments->lhs->Analyse(this);

	if (IsLiteral && Definition->FunctionData.ParameterData[0].IsPassByReference && !Definition->FunctionData.ParameterData[0].IsConst)
	{
		ThrowError("Cannot pass a literal by reference unless it's a const argument. First argument in " + name + ".");
	}

	IsLiteral = false;
	TwoArguments->rhs->Analyse(this);

	if (IsLiteral && Definition->FunctionData.ParameterData[1].IsPassByReference && !Definition->FunctionData.ParameterData[1].IsConst)
	{
		ThrowError("Cannot pass a literal by reference unless it's a const argument. Second argument in " + name + ".");
	}
	IsLiteral = false;

}

void USAP_Literal::Analyse(UAST_OneArgument* OneArgument)
{
	FString name = "operator " + OneArgument->GetDescription();
	FExpressionReturn* ArgReturn = GetSymbolTable()->ExpressionReturns.Find(OneArgument->Argument);

	TArray<FParamSignature> paramSig;
	paramSig.Add(FParamSignature(ArgReturn->ReturnType, ArgReturn->ReturnsArray()));

	// Get definition
	UAST_FunctionDefinition* Definition = GetSymbolTable()->GetOverloadedOperator(FFunctionSignature(name, paramSig));


	IsLiteral = false;
	OneArgument->Argument->Analyse(this);

	if (IsLiteral && Definition->FunctionData.ParameterData[0].IsPassByReference && !Definition->FunctionData.ParameterData[0].IsConst)
	{
		ThrowError("Cannot pass a literal by reference unless it's a const argument. In " + name + ".");
	}
	IsLiteral = false;
}

void USAP_Literal::Analyse(UAST_MemberAccess* MemberAccess)
{
	// Analyse lhs
	MemberAccess->lhs->Analyse(this);

	// Set lhs as current owner
	UAST_ClassDefinition* previousCaller = Caller;
	FExpressionReturn expRet = GetSymbolTable()->ExpressionReturns[MemberAccess->lhs];
	if (expRet.ReturnsArray())
	{
		ElementType = expRet.ReturnType;
		Caller = GetSymbolTable()->ClassNames["array"];
	}
	else
	{
		ElementType = "";
		Caller = GetSymbolTable()->ClassNames[expRet.ReturnType];
	}

	// Analyse rhs
	MemberAccess->rhs->Analyse(this);

	// Return previous owner
	Caller = previousCaller;
	ElementType = "";
}

void USAP_Literal::Analyse(UAST_Scope* Scope)
{
	IsLiteral = false;
	for (UAST_Node* currentNode : Scope->GetChildren())
	{
		currentNode->Analyse(this);
		IsLiteral = false;
	}
}

void USAP_Literal::Analyse(UAST_Return* Return)
{
	if (!Return->ReturnExpression) return;

	Return->ReturnExpression->Analyse(this);
}

void USAP_Literal::Analyse(UAST_NullptrLiteral* Nullptr)
{
	IsLiteral = true;
}

void USAP_Literal::Analyse(UAST_Expression* Expression)
{
	AnalyseChildren(Expression);
}

void USAP_Literal::Analyse(UAST_BoolLiteral* BoolLiteral)
{
	IsLiteral = true;
}

void USAP_Literal::Analyse(UAST_FloatLiteral* FloatLiteral)
{
	IsLiteral = true;
}

void USAP_Literal::Analyse(UAST_IntLiteral* IntLiteral)
{
	IsLiteral = true;
}

void USAP_Literal::Analyse(UAST_StringLiteral* StringLiteral)
{
	IsLiteral = true;
}
