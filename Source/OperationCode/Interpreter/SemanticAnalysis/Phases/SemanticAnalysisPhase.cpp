// Fill out your copyright notice in the Description page of Project Settings.

#include "SemanticAnalysisPhase.h"
#include "Interpreter/SemanticAnalysis/SemanticAnalysis.h"

#include "Interpreter/Parser/AST/AST_Basic.h"
#include "Interpreter/Parser/AST/AST_Break.h"
#include "Interpreter/Parser/AST/AST_Continue.h"
#include "Interpreter/Parser/AST/AST_Main.h"
#include "Interpreter/Parser/AST/AST_Return.h"
#include "Interpreter/Parser/AST/AST_Scope.h"

#include "Interpreter/Parser/AST/Definition/AST_ClassDefinition.h"
#include "Interpreter/Parser/AST/Definition/AST_FunctionDefinition.h"
#include "Interpreter/Parser/AST/Definition/AST_VariableDefinition.h"

#include "Interpreter/Parser/AST/Expressions/Calls/AST_FunctionCall.h"
#include "Interpreter/Parser/AST/Expressions/Calls/AST_VariableCall.h"

#include "Interpreter/Parser/AST/Expressions/Literals/AST_BoolLiteral.h"
#include "Interpreter/Parser/AST/Expressions/Literals/AST_FloatLiteral.h"
#include "Interpreter/Parser/AST/Expressions/Literals/AST_IntLiteral.h"
#include "Interpreter/Parser/AST/Expressions/Literals/AST_StringLiteral.h"

#include "Interpreter/Parser/AST/Expressions/Operators/AST_Operator.h"
#include "Interpreter/Parser/AST/Expressions/Operators/TwoArguments/AST_MemberAccess.h"


void USemanticAnalysisPhase::Init(USemanticAnalysis* Analyser)
{
	SemanticAnalysis = Analyser;
}

void USemanticAnalysisPhase::StartAnalysis(UAST_Node* RootNode)
{
	RootNode->Analyse(this);
}


void USemanticAnalysisPhase::ThrowError(FString ErrorMessage)
{
	SemanticAnalysis->ThrowError(ErrorMessage);
}

bool USemanticAnalysisPhase::HasErrors() const
{
	return SemanticAnalysis->HasErrors(); 
}

USymbolTable* USemanticAnalysisPhase::GetSymbolTable() const
{
	if (!GetAnalyser()) return nullptr;
	return GetAnalyser()->GetMainSymbolTable();
}

void USemanticAnalysisPhase::AnalyseChildren(UAST_Node* Node)
{
	for (UAST_Node* currentChild : Node->GetChildren())
	{
		currentChild->Analyse(this);
	}
}

/*

void USemanticAnalysisPhase::Analyse(UAST_Basic* Basic)
{

}

void USemanticAnalysisPhase::Analyse(UAST_Main* Main)
{

}

void USemanticAnalysisPhase::Analyse(UAST_ClassDefinition* ClassDefinition)
{

}

void USemanticAnalysisPhase::Analyse(UAST_FunctionDefinition* FunctionDefinition)
{

}

void USemanticAnalysisPhase::Analyse(UAST_VariableDefinition* VariableDefinition)
{

}

void USemanticAnalysisPhase::Analyse(UAST_Loop* Loop)
{

}

void USemanticAnalysisPhase::Analyse(UAST_DoWhile* DoWhile)
{

}

void USemanticAnalysisPhase::Analyse(UAST_For* For)
{

}

void USemanticAnalysisPhase::Analyse(UAST_If* If)
{

}

void USemanticAnalysisPhase::Analyse(UAST_While* While)
{

}

void USemanticAnalysisPhase::Analyse(UAST_FunctionCall* FunctionCall)
{

}

void USemanticAnalysisPhase::Analyse(UAST_VariableCall* VariableCall)
{

}

void USemanticAnalysisPhase::Analyse(UAST_BoolLiteral* BoolLiteral)
{

}

void USemanticAnalysisPhase::Analyse(UAST_FloatLiteral* FloatLiteral)
{

}

void USemanticAnalysisPhase::Analyse(UAST_IntLiteral* IntLiteral)
{

}

void USemanticAnalysisPhase::Analyse(UAST_StringLiteral* StringLiteral)
{

}

void USemanticAnalysisPhase::Analyse(UAST_Operator* Operator)
{

}

void USemanticAnalysisPhase::Analyse(UAST_TwoArguments* TwoArguments)
{

}

void USemanticAnalysisPhase::Analyse(UAST_OneArgument* OneArgument)
{

}

void USemanticAnalysisPhase::Analyse(UAST_MemberAccess* MemberAccess)
{

}

void USemanticAnalysisPhase::Analyse(UAST_Scope* Scope)
{

}

void USemanticAnalysisPhase::Analyse(UAST_Return* Return)
{

}

void USemanticAnalysisPhase::Analyse(UAST_Break* Break)
{

}

void USemanticAnalysisPhase::Analyse(UAST_Continue* Continue)
{

}

*/
