// Fill out your copyright notice in the Description page of Project Settings.

#include "SemanticAnalysis.h"
#include "SymbolTable.h"

#include "Phases/SAP_ClassAnalysis.h"
#include "Phases/SAP_ConvertVariableCallsToType.h"
#include "Phases/SAP_FunctionAnalysis.h"
#include "Phases/SAP_StoreStatics.h"
#include "Phases/SAP_OperatorAnalysis.h"
#include "Phases/SAP_ExpressionAnalysis.h"
#include "Phases/SAP_StaticAnalysis.h"
#include "Phases/SAP_FlowControlAnalysis.h"
#include "Phases/SAP_ReturnAnalysis.h"
#include "Phases/SAP_Final.h"
#include "Phases/SAP_Const.h"
#include "Phases/SAP_Literal.h"



USemanticAnalysis::USemanticAnalysis()
{
	PhaseClasses.Add(USAP_ClassAnalysis::StaticClass());
	PhaseClasses.Add(USAP_ConvertVariableCallsToType::StaticClass());
	PhaseClasses.Add(USAP_FunctionAnalysis::StaticClass());
	PhaseClasses.Add(USAP_OperatorAnalysis::StaticClass());
	PhaseClasses.Add(USAP_StoreStatics::StaticClass());
	PhaseClasses.Add(USAP_ExpressionAnalysis::StaticClass());
	PhaseClasses.Add(USAP_StaticAnalysis::StaticClass());
	PhaseClasses.Add(USAP_FlowControlAnalysis::StaticClass());
	PhaseClasses.Add(USAP_ReturnAnalysis::StaticClass());
	PhaseClasses.Add(USAP_Final::StaticClass());
	PhaseClasses.Add(USAP_Const::StaticClass());
	PhaseClasses.Add(USAP_Literal::StaticClass());
}

void USemanticAnalysis::Clear()
{
	Super::Clear();

	MainSymbolTable = NewObject<USymbolTable>(GetInterpreter());
	Phases.Empty(PhaseClasses.Num());

	for (TSubclassOf<USemanticAnalysisPhase> CurrentPhaseClass : PhaseClasses)
	{
		USemanticAnalysisPhase* newPhase = NewObject<USemanticAnalysisPhase>(this, CurrentPhaseClass);
		newPhase->Init(this);
		Phases.Add(newPhase);
	}
}

USymbolTable* USemanticAnalysis::AnalyseAST(UAST_Node* Root, UValue* TopOwner)
{
	// Clear previous data
	Clear();
	MainSymbolTable->TopOwner = TopOwner;

	for (USemanticAnalysisPhase* currentPhase : Phases)
	{
		currentPhase->StartAnalysis(Root);
		if (HasErrors()) break;
	}

	return MainSymbolTable;
}


