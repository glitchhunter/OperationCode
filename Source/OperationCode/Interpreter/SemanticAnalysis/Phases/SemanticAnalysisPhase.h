// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"

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
#include "Interpreter/Parser/AST/Expressions/Literals/AST_NullptrLiteral.h"

#include "Interpreter/Parser/AST/FlowControl/Loops/AST_DoWhile.h"
#include "Interpreter/Parser/AST/FlowControl/Loops/AST_While.h"
#include "Interpreter/Parser/AST/FlowControl/Loops/AST_For.h"
#include "Interpreter/Parser/AST/FlowControl/AST_If.h"

#include "Interpreter/Parser/AST/Expressions/Operators/AST_Operator.h"
#include "Interpreter/Parser/AST/Expressions/Operators/TwoArguments/AST_MemberAccess.h"
#include "Interpreter/Parser/AST/Expressions/Operators/OneArgument/AST_OneArgument.h"
#include "Interpreter/Parser/AST/Expressions/AST_Type.h"

#include "SemanticAnalysisPhase.generated.h"




/**
 * 
 */
UCLASS(ABSTRACT)
class OPERATIONCODE_API USemanticAnalysisPhase : public UObject
{
	GENERATED_BODY()

public:

	void Init(USemanticAnalysis* Analyser);

	virtual void StartAnalysis(UAST_Node* RootNode);


	// For compilation only
	virtual void Analyse(UAST_Node* Node) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_Node*), );

	virtual void Analyse(UAST_Basic* Basic) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_Basic*), );

	virtual void Analyse(UAST_Main* Main) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_Main*), );

	virtual void Analyse(UAST_ClassDefinition* ClassDefinition) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_ClassDefinition*), );

	virtual void Analyse(UAST_FunctionDefinition* FunctionDefinition) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_FunctionDefinition*), );

	virtual void Analyse(UAST_VariableDefinition* VariableDefinition) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_VariableDefinition*), );

	virtual void Analyse(UAST_DoWhile* DoWhile) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_DoWhile*), );

	virtual void Analyse(UAST_For* For) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_For*), );

	virtual void Analyse(UAST_If* If) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_If*), );

	virtual void Analyse(UAST_While* While) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_While*), );

	virtual void Analyse(UAST_FunctionCall* FunctionCall) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_FunctionCall*), );

	virtual void Analyse(UAST_VariableCall* VariableCall) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_VariableCall*), );

	virtual void Analyse(UAST_BoolLiteral* BoolLiteral) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_BoolLiteral*), );

	virtual void Analyse(UAST_FloatLiteral* FloatLiteral) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_FloatLiteral*), );

	virtual void Analyse(UAST_IntLiteral* IntLiteral) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_IntLiteral*), );

	virtual void Analyse(UAST_StringLiteral* StringLiteral) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_StringLiteral*), );

	virtual void Analyse(UAST_TwoArguments* TwoArguments) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_TwoArguments*), );

	virtual void Analyse(UAST_OneArgument* OneArgument) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_OneArgument*), );

	virtual void Analyse(UAST_MemberAccess* MemberAccess) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_MemberAccess*), );

	virtual void Analyse(UAST_Scope* Scope) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_Scope*), );

	virtual void Analyse(UAST_Return* Return) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_Return*), );

	virtual void Analyse(UAST_Break* Break) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_Break*), );

	virtual void Analyse(UAST_Continue* Continue) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_Continue*), );

	virtual void Analyse(UAST_Type* Type) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_Type*), );

	virtual void Analyse(UAST_Expression* Expression) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_Expression*), );

	virtual void Analyse(UAST_NullptrLiteral* Nullptr) PURE_VIRTUAL(USemanticAnalysisPhase::Analyse(UAST_NullptrLiteral*), );


protected:

	virtual void ThrowError(FString ErrorMessage);

	USemanticAnalysis* GetAnalyser() const { return SemanticAnalysis; }

	bool HasErrors() const;

	USymbolTable* GetSymbolTable() const;

	void AnalyseChildren(UAST_Node* Node);


private:

	UPROPERTY()
	USemanticAnalysis* SemanticAnalysis;
	
	
};



/*



virtual void Analyse(UAST_Basic* Basic) override;

virtual void Analyse(UAST_Main* Main) override;

virtual void Analyse(UAST_ClassDefinition* ClassDefinition) override;

virtual void Analyse(UAST_FunctionDefinition* FunctionDefinition) override;

virtual void Analyse(UAST_VariableDefinition* VariableDefinition) override;

virtual void Analyse(UAST_DoWhile* DoWhile) override;

virtual void Analyse(UAST_For* For) override;

virtual void Analyse(UAST_If* If) override;

virtual void Analyse(UAST_While* While) override;

virtual void Analyse(UAST_FunctionCall* FunctionCall) override;

virtual void Analyse(UAST_VariableCall* VariableCall) override;

virtual void Analyse(UAST_BoolLiteral* BoolLiteral) override;

virtual void Analyse(UAST_FloatLiteral* FloatLiteral) override;

virtual void Analyse(UAST_IntLiteral* IntLiteral) override;

virtual void Analyse(UAST_StringLiteral* StringLiteral) override;

virtual void Analyse(UAST_TwoArguments* TwoArguments) override;

virtual void Analyse(UAST_OneArgument* OneArgument) override;

virtual void Analyse(UAST_MemberAccess* MemberAccess) override;

virtual void Analyse(UAST_Scope* Scope) override;

virtual void Analyse(UAST_Return* Return) override;

virtual void Analyse(UAST_Break* Break) override;

virtual void Analyse(UAST_Continue* Continue) override;

virtual void Analyse(UAST_Type* Type) override;

virtual void Analyse(UAST_Expression* Expression) override;


*/

