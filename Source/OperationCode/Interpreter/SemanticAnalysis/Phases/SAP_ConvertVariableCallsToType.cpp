// Fill out your copyright notice in the Description page of Project Settings.

#include "SAP_ConvertVariableCallsToType.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/SemanticAnalysis/SymbolTable.h"

#include "Interpreter/Parser/AST/AST_Basic.h"
#include "Interpreter/Parser/AST/AST_Main.h"
#include "Interpreter/Parser/AST/AST_Return.h"
#include "Interpreter/Parser/AST/AST_Scope.h"

#include "Interpreter/Parser/AST/Definition/AST_ClassDefinition.h"
#include "Interpreter/Parser/AST/Definition/AST_FunctionDefinition.h"
#include "Interpreter/Parser/AST/Definition/AST_VariableDefinition.h"

#include "Interpreter/Parser/AST/Expressions/Calls/AST_FunctionCall.h"
#include "Interpreter/Parser/AST/Expressions/Calls/AST_VariableCall.h"

#include "Interpreter/Parser/AST/FlowControl/Loops/AST_DoWhile.h"
#include "Interpreter/Parser/AST/FlowControl/Loops/AST_For.h"
#include "Interpreter/Parser/AST/FlowControl/Loops/AST_While.h"
#include "Interpreter/Parser/AST/FlowControl/AST_If.h"

#include "Interpreter/Parser/AST/Expressions/Operators/OneArgument/AST_OneArgument.h"
#include "Interpreter/Parser/AST/Expressions/Operators/TwoArguments/AST_TwoArguments.h"

#include "Interpreter/Parser/AST/Expressions/AST_Type.h"


UAST_Type* USAP_ConvertVariableCallsToType::CreateType(UAST_Node* Parent)
{
	UAST_Type* Type = NewObject<UAST_Type>(Parent->GetOuter());
	Type->Type = VariableCallToConvert->VariableName;
	VariableCallToConvert = nullptr;
	return Type;
}


/*======================
 Basic
======================*/

void USAP_ConvertVariableCallsToType::Analyse(UAST_Basic* Basic)
{
	AnalyseChildren(Basic);
}


/*======================
 Main
======================*/

void USAP_ConvertVariableCallsToType::Analyse(UAST_Main* Main) 
{
	for (int i = 0; i < Main->GetChildren().Num(); ++i)
	{
		Main->GetChildren()[i]->Analyse(this);
		if (CanConvert()) Main->Children[i] = CreateType(Main);
	}
}


/*======================
Class definition
======================*/

void USAP_ConvertVariableCallsToType::Analyse(UAST_ClassDefinition* ClassDefinition) 
{
	AnalyseChildren(ClassDefinition);
}


/*======================
 Function definition
======================*/

void USAP_ConvertVariableCallsToType::Analyse(UAST_FunctionDefinition* FunctionDefinition) 
{
	AnalyseChildren(FunctionDefinition);
}


/*======================
 Variable definition
======================*/

void USAP_ConvertVariableCallsToType::Analyse(UAST_VariableDefinition* VariableDefinition)
{
	if (!VariableDefinition->InitExpression) return;
	VariableDefinition->InitExpression->Analyse(this);
	if (CanConvert()) VariableDefinition->InitExpression = CreateType(VariableDefinition);
}


/*======================
 Do while
======================*/

void USAP_ConvertVariableCallsToType::Analyse(UAST_DoWhile* DoWhile) 
{
	DoWhile->Condition->Analyse(this);
	if (CanConvert()) DoWhile->Condition = CreateType(DoWhile);

	DoWhile->Body->Analyse(this);
	if (CanConvert()) DoWhile->Body = CreateType(DoWhile);
}


/*======================
 For
======================*/

void USAP_ConvertVariableCallsToType::Analyse(UAST_For* For)
{
	For->Initialization->Analyse(this);

	For->Condition->Analyse(this);
	if (CanConvert()) For->Condition = CreateType(For);

	For->Update->Analyse(this);
	if (CanConvert()) For->Update = CreateType(For);

	For->Body->Analyse(this);
	if (CanConvert()) For->Body = CreateType(For);
}


/*======================
 If
======================*/

void USAP_ConvertVariableCallsToType::Analyse(UAST_If* If)
{
	If->Condition->Analyse(this);
	if (CanConvert()) If->Condition = CreateType(If);

	If->TrueBranch->Analyse(this);
	if (CanConvert()) If->TrueBranch = CreateType(If);

	if (!If->FalseBranch) return;
	If->FalseBranch->Analyse(this);
	if (CanConvert()) If->FalseBranch = CreateType(If);
}


/*======================
 While
======================*/

void USAP_ConvertVariableCallsToType::Analyse(UAST_While* While) 
{
	While->Condition->Analyse(this);
	if (CanConvert()) While->Condition = CreateType(While);

	While->Body->Analyse(this);
	if (CanConvert()) While->Body = CreateType(While);
}


/*======================
 FunctionCall
======================*/

void USAP_ConvertVariableCallsToType::Analyse(UAST_FunctionCall* FunctionCall) 
{
	for (int i = 0; i < FunctionCall->Arguments.Num(); ++i)
	{
		FunctionCall->Arguments[i]->Analyse(this);
		if (CanConvert()) FunctionCall->Arguments[i] = CreateType(FunctionCall);
	}
}


/*======================
 Variable call
======================*/

void USAP_ConvertVariableCallsToType::Analyse(UAST_VariableCall* VariableCall) 
{
	if (!GetSymbolTable()->ClassNames.Contains(VariableCall->VariableName)) return;

	// Mark variable call for conversion
	VariableCallToConvert = VariableCall;
}


/*======================
 Two arguments
======================*/

void USAP_ConvertVariableCallsToType::Analyse(UAST_TwoArguments* TwoArguments) 
{
	TwoArguments->lhs->Analyse(this);
	if (CanConvert()) TwoArguments->lhs = CreateType(TwoArguments);

	TwoArguments->rhs->Analyse(this);
	if (CanConvert()) TwoArguments->rhs = CreateType(TwoArguments);
}


/*======================
 Member access
======================*/

void USAP_ConvertVariableCallsToType::Analyse(UAST_MemberAccess* MemberAccess)
{
	MemberAccess->lhs->Analyse(this);
	if (CanConvert()) MemberAccess->lhs = CreateType(MemberAccess);

	MemberAccess->rhs->Analyse(this);
	if (CanConvert()) MemberAccess->rhs = CreateType(MemberAccess);
}

/*======================
 One argument
======================*/

void USAP_ConvertVariableCallsToType::Analyse(UAST_OneArgument* OneArgument)
{
	OneArgument->Argument->Analyse(this);
	if (CanConvert()) OneArgument->Argument = CreateType(OneArgument);
}


/*======================
 Scope
======================*/

void USAP_ConvertVariableCallsToType::Analyse(UAST_Scope* Scope) 
{
	for (int i = 0; i < Scope->Children.Num(); ++i)
	{
		Scope->Children[i]->Analyse(this);
		if (CanConvert()) Scope->Children[i] = CreateType(Scope);
	}
}


/*======================
 Return
======================*/

void USAP_ConvertVariableCallsToType::Analyse(UAST_Return* Return) 
{
	if (!Return->ReturnExpression) return;

	Return->ReturnExpression->Analyse(this);
	if (CanConvert()) Return->ReturnExpression = CreateType(Return);
}


/*======================
 Type
======================*/

void USAP_ConvertVariableCallsToType::Analyse(UAST_Type* Type)
{
	if (GetSymbolTable()->ClassNames.Contains(Type->Type)) return;
	ThrowError("Unknown type \"" + Type->Type + "\" detected.");	
}




