// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "SAP_ConvertVariableCallsToType.generated.h"

/**
 * ** Modifies AST tree! **
 * During the parsing phase, we don't have enough info to find out if an identifier
 * is a variable call or a type. ID.function() can mean two things. ID is a variable,
 * and we call a function on its value, or ID is a type, and we call a static function.
 *
 * After analysing classes, we have enough info to loop through all the nodes,
 * and convert variable calls to types where applicable.
 */
UCLASS()
class OPERATIONCODE_API USAP_ConvertVariableCallsToType : public USemanticAnalysisPhase
{
	GENERATED_BODY()
	
public:
	

	virtual void Analyse(UAST_Basic* Basic);

	virtual void Analyse(UAST_Main* Main);

	virtual void Analyse(UAST_ClassDefinition* ClassDefinition);

	virtual void Analyse(UAST_FunctionDefinition* FunctionDefinition);

	virtual void Analyse(UAST_VariableDefinition* VariableDefinition);

	virtual void Analyse(UAST_DoWhile* DoWhile);

	virtual void Analyse(UAST_For* For);

	virtual void Analyse(UAST_If* If);

	virtual void Analyse(UAST_While* While);

	virtual void Analyse(UAST_FunctionCall* FunctionCall);

	virtual void Analyse(UAST_VariableCall* VariableCall);

	virtual void Analyse(UAST_TwoArguments* TwoArguments);

	virtual void Analyse(UAST_MemberAccess* MemberAccess);

	virtual void Analyse(UAST_OneArgument* OneArgument);

	virtual void Analyse(UAST_Scope* Scope);

	virtual void Analyse(UAST_Return* Return);

	virtual void Analyse(UAST_Type* Type);





	virtual void Analyse(UAST_BoolLiteral* BoolLiteral) override {}

	virtual void Analyse(UAST_FloatLiteral* FloatLiteral) override {}

	virtual void Analyse(UAST_IntLiteral* IntLiteral) override {}

	virtual void Analyse(UAST_StringLiteral* StringLiteral) override {}

	virtual void Analyse(UAST_Break* Break) override {}

	virtual void Analyse(UAST_Continue* Continue) override {}

	virtual void Analyse(UAST_Expression* Expression) override {}

	virtual void Analyse(UAST_NullptrLiteral* Nullptr) override {}

private:

	UAST_Type* CreateType(UAST_Node* Parent);

	bool CanConvert() const { return VariableCallToConvert != nullptr; }

	UPROPERTY()
	UAST_VariableCall* VariableCallToConvert;

	
	
};
