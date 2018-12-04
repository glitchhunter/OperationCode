// Fill out your copyright notice in the Description page of Project Settings.

#include "SAP_Const.h"
#include "Interpreter/SemanticAnalysis/SymbolTable.h"

void USAP_Const::StartAnalysis(UAST_Node* RootNode)
{
	TArray<UAST_FunctionDefinition*> AllFunctionDefinitions;
	GetSymbolTable()->FunctionIDs.GenerateValueArray(AllFunctionDefinitions);

	for (auto it = GetSymbolTable()->FunctionIDs.CreateConstIterator(); it; ++it)
	{
		OwningClasss = it.Key().ClassDefinition;
		AnalyseFunction(it.Value());
	}

	// A probably unecessary cleanup
	CurrentFunction = nullptr;
	OwningClasss = nullptr;
}


void USAP_Const::AnalyseFunction(UAST_FunctionDefinition* Function)
{
	// Cleanup
	ScopeVars.Empty();
	NonConstParams.Empty();
	ConstParams.Empty();
	CurrentVarName = "";
	CallerIsThis = true;

	// If there is no scope, function body is defined in cpp or blueprint.
	if (!Function->Scope) return;

	// Store current function
	CurrentFunction = Function;

	// Populate param sets
	for (FParameterData currentParam : Function->FunctionData.ParameterData)
	{
		if (currentParam.IsConst) ConstParams.Add(currentParam.Name);
		else NonConstParams.Add(currentParam.Name);
	}

	// Start analysing the function body
	Function->Scope->Analyse(this);

}






void USAP_Const::Analyse(UAST_VariableDefinition* VariableDefinition)
{
	// Add a variable definition in current scope
	ScopeVars.Top().Add(VariableDefinition->Name);

	// Analyse init expression if it exists
	if (VariableDefinition->InitExpression)
		VariableDefinition->InitExpression->Analyse(this);
}

void USAP_Const::Analyse(UAST_DoWhile* DoWhile)
{
	// Add a scope
	ScopeVars.Add(TSet<FString>());

	DoWhile->Condition->Analyse(this);
	DoWhile->Body->Analyse(this);

	// RemoveScope
	ScopeVars.Pop();
}

void USAP_Const::Analyse(UAST_For* For)
{
	// Add a scope
	ScopeVars.Add(TSet<FString>());

	if (For->Initialization) For->Initialization->Analyse(this);
	For->Condition->Analyse(this);
	if (For->Update) For->Update->Analyse(this);
	For->Body->Analyse(this);

	// RemoveScope
	ScopeVars.Pop();
}


void USAP_Const::Analyse(UAST_If* If)
{
	If->Condition->Analyse(this);
	If->TrueBranch->Analyse(this);
	if (If->FalseBranch) If->FalseBranch->Analyse(this);
}

void USAP_Const::Analyse(UAST_While* While)
{
	// Add a scope
	ScopeVars.Add(TSet<FString>());

	While->Body->Analyse(this);
	While->Condition->Analyse(this);

	// RemoveScope
	ScopeVars.Pop();
}

void USAP_Const::Analyse(UAST_FunctionCall* FunctionCall)
{
	UAST_ClassDefinition* own; 
	UAST_FunctionDefinition* thisDefinition;

	if (CallerIsThis) own = OwningClasss;
	else own = GetSymbolTable()->ClassNames[secondaryOwner];


	// Check member functions
	TArray<UAST_FunctionDefinition*> FunDefs = GetSymbolTable()->GetFunctionDefinitions(FunctionCall, own, ElementType, true);
	if (FunDefs.Num() == 0)
	{
		// Check if function belongs in top owner
		if (GetSymbolTable()->TopOwner)
		{
			own = GetSymbolTable()->ClassNames[GetSymbolTable()->TopOwner->Type];
			FunDefs = GetSymbolTable()->GetFunctionDefinitions(FunctionCall, own, ElementType, true);
		}

		if (FunDefs.Num() == 0)
		{
			// check for global static functions
			own = nullptr;
			FunDefs = GetSymbolTable()->GetFunctionDefinitions(FunctionCall, own, ElementType, true);

			if (FunDefs.Num() == 0)
			{
				ThrowError("Cannot find matching function named " + FunctionCall->FunctionName + " in const analysis.");
				return;
			}
		}
	}

	// We found the definition
	thisDefinition = FunDefs[0];


	// If this is the caller, then the function must be const
	if (own && CurrentFunction->FunctionData.IsConst && !thisDefinition->FunctionData.IsConst)
	{
		ThrowError("Calling a non-const function \"" + thisDefinition->FunctionData.FunctionName + "\" inside a const function \""
			+ CurrentFunction->FunctionData.FunctionName + "\".");
	}

	// Analyse all arguments
	for (int i = 0; i < FunctionCall->Arguments.Num(); ++i)
	{
		FunctionCall->Arguments[i]->Analyse(this);

		// Skip if this argument does not have an interesting variable
		if (CurrentVarName == "") continue;

		// Throw error if we pass a const variable by reference, while not marked as const
		if (thisDefinition->FunctionData.ParameterData[i].IsPassByReference && !thisDefinition->FunctionData.ParameterData[i].IsConst)
		{
			ThrowError("Attempting to pass a const variable " + CurrentVarName + " as a non const pass by reference argument in function \""
				+ thisDefinition->FunctionData.FunctionName + "\".");
		}
	}
}

void USAP_Const::Analyse(UAST_VariableCall* VariableCall)
{
	// Check if variable is local, starting from inner most scope
	for (int i = ScopeVars.Num() - 1; i >= 0; --i)
	{
		// If this is a local variable, then it is const correct
		if (ScopeVars[i].Contains(VariableCall->VariableName)) return;
	}

	// If it is not a global variable, check if it is static
	TArray<FString> StaticVariableNames;
	GetSymbolTable()->StaticVariables.GetKeys(StaticVariableNames);

	// If this is a static variable, then it is const correct
	if (StaticVariableNames.Contains(VariableCall->VariableName)) return;

	// This variable is a non const parameter, so it is const correct
	if (NonConstParams.Contains(VariableCall->VariableName)) return;

	// If this is a const parameter, then this is not const correct
	if (ConstParams.Contains(VariableCall->VariableName))
	{
		CurrentVarName = VariableCall->VariableName;
		return;
	}

	// Only other option is that this is a member variable.
	if (CurrentFunction->FunctionData.IsConst)
		CurrentVarName = VariableCall->VariableName;
}

void USAP_Const::Analyse(UAST_TwoArguments* TwoArguments)
{
	UAST_FunctionDefinition* Definition = nullptr;
	TwoArguments->lhs->Analyse(this);

	// lhs is a variable we are interested in
	if (CurrentVarName != "")
	{
		FString name = "operator " + TwoArguments->GetDescription();
		FExpressionReturn* lhsReturn = GetSymbolTable()->ExpressionReturns.Find(TwoArguments->lhs);
		FExpressionReturn* rhsReturn = GetSymbolTable()->ExpressionReturns.Find(TwoArguments->rhs);

		TArray<FParamSignature> paramSig;
		paramSig.Add(FParamSignature(lhsReturn->ReturnType, lhsReturn->ReturnsArray()));
		paramSig.Add(FParamSignature(rhsReturn->ReturnType, rhsReturn->ReturnsArray()));

		// Get definition
		Definition = GetSymbolTable()->GetOverloadedOperator(FFunctionSignature(name, paramSig));


		if (!Definition->FunctionData.ParameterData[0].IsConst)
		{
			ThrowError("Trying to pass a variable \"" + CurrentVarName + "\" as first argument of " + name + ".");
			CurrentVarName = "";
		}
	}

	TwoArguments->rhs->Analyse(this);
	{
		if (!Definition)
		{
			FString name = "operator " + TwoArguments->GetDescription();
			FExpressionReturn* lhsReturn = GetSymbolTable()->ExpressionReturns.Find(TwoArguments->lhs);
			FExpressionReturn* rhsReturn = GetSymbolTable()->ExpressionReturns.Find(TwoArguments->rhs);

			TArray<FParamSignature> paramSig;
			paramSig.Add(FParamSignature(lhsReturn->ReturnType, lhsReturn->ReturnsArray()));
			paramSig.Add(FParamSignature(rhsReturn->ReturnType, rhsReturn->ReturnsArray()));

			// Get definition
			Definition = GetSymbolTable()->GetOverloadedOperator(FFunctionSignature(name, paramSig));
		}

		if (!Definition->FunctionData.ParameterData[1].IsConst)
		{
			ThrowError("Trying to pass a variable \"" + CurrentVarName + "\" as second argument of operator " 
				+ TwoArguments->GetDescription() + ".");
			CurrentVarName = "";
		}
	}




}

void USAP_Const::Analyse(UAST_OneArgument* OneArgument)
{
	OneArgument->Argument->Analyse(this);

	// lhs is a variable we are interested in
	if (CurrentVarName != "")
	{
		FString name = "operator " + OneArgument->GetDescription();
		FExpressionReturn* ArgReturn = GetSymbolTable()->ExpressionReturns.Find(OneArgument->Argument);

		TArray<FParamSignature> paramSig;
		paramSig.Add(FParamSignature(ArgReturn->ReturnType, ArgReturn->ReturnsArray()));

		// Get definition
		UAST_FunctionDefinition* Definition = GetSymbolTable()->GetOverloadedOperator(FFunctionSignature(name, paramSig));


		if (!Definition->FunctionData.ParameterData[0].IsConst)
		{
			ThrowError("Trying to pass a variable \"" + CurrentVarName + "\" as first argument of " + name + ".");
			CurrentVarName = "";
		}
	}

}

void USAP_Const::Analyse(UAST_MemberAccess* MemberAccess)
{
	// Analyse lhs.
	MemberAccess->lhs->Analyse(this);
	CallerIsThis = false;

	FExpressionReturn expRet = GetSymbolTable()->ExpressionReturns[MemberAccess->lhs];
	if (expRet.ReturnsArray())
	{
		secondaryOwner = "array";
		ElementType = expRet.ReturnType;
	}
	else
	{
		secondaryOwner = expRet.ReturnType;
		ElementType = "";
	}

	// If member we are accessing is not a variable we are interested in, skip it
	if (CurrentVarName == "")
	{
		CallerIsThis = true;
		return;
	}

	// Analyse rhs
	MemberAccess->rhs->Analyse(this);
	CallerIsThis = true;
	secondaryOwner = "";
	ElementType = "";

	// We are done with this variable
	CurrentVarName = "";
}

void USAP_Const::Analyse(UAST_Scope* Scope)
{
	// Add scope as we enter
	ScopeVars.Add(TSet<FString>());

	// Analyse all contents
	for (UAST_Node* currentNode : Scope->GetChildren())
	{
		currentNode->Analyse(this);
	}

	// Pop scope as we leave
	ScopeVars.Pop();
}

void USAP_Const::Analyse(UAST_Return* Return)
{
	if (Return->ReturnExpression) 
		Return->ReturnExpression->Analyse(this);
}

