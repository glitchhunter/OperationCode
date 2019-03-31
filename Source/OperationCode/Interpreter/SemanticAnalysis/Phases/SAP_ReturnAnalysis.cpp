// Fill out your copyright notice in the Description page of Project Settings.

#include "SAP_ReturnAnalysis.h"
#include "Interpreter/SemanticAnalysis/SymbolTable.h"

bool USAP_ReturnAnalysis::IsInVoidFunction()
{
	return (CurrentFunction && CurrentFunction->FunctionData.ReturnType == "void");
}


void USAP_ReturnAnalysis::StartAnalysis(UAST_Node* Root)
{
	for (auto pair : GetSymbolTable()->FunctionIDs)
	{
		CurrentFunction = pair.Value;
		PathHasReturn = false;

		if (!CurrentFunction->Scope) continue;
		CurrentFunction->Scope->Analyse(this);

		if (!PathHasReturn && !IsInVoidFunction())
		{
			ThrowError("Not all execution paths return a value in \"" + CurrentFunction->FunctionData.FunctionName + "\".");
		}
	}
}



/*======================
 Scope
======================*/

void USAP_ReturnAnalysis::Analyse(UAST_Scope* Scope)
{
	bool LocalPathHasReturn = PathHasReturn;
	for (UAST_Node* currentChild : Scope->GetChildren())
	{
		if (LocalPathHasReturn)
		{
			// @TODO: Add warning for unreachable code
		}

		currentChild->Analyse(this);

		// If scope has a return path, it will always have a return path
		if (!LocalPathHasReturn) LocalPathHasReturn = PathHasReturn;
	}

	PathHasReturn = LocalPathHasReturn;
}


/*======================
 If
======================*/

void USAP_ReturnAnalysis::Analyse(UAST_If* If)
{
	bool LocalTrueHasReturn = false;
	bool LocalFalseHasReturn = false;
	PathHasReturn = false;

	If->TrueBranch->Analyse(this);
	LocalTrueHasReturn = PathHasReturn;
	// Reset return path for false branch
	PathHasReturn = false;

	// If there is no false branch, then branch does not have a return path
	if (If->FalseBranch)
	{
		If->FalseBranch->Analyse(this);
		LocalFalseHasReturn = PathHasReturn;
	}

	PathHasReturn = LocalTrueHasReturn && LocalFalseHasReturn;
}


/*======================
 While
======================*/

void USAP_ReturnAnalysis::Analyse(UAST_While* While)
{
	// There is no guarantee that any code inside a while loop will run
}


/*======================
 For
======================*/

void USAP_ReturnAnalysis::Analyse(UAST_For* For)
{
	// There is no guarantee that any code inside a for loop will run
}


/*======================
 Do while
======================*/

void USAP_ReturnAnalysis::Analyse(UAST_DoWhile* DoWhile)
{
	// Do while is the only loop where the loop body must be run at least once,
	// However, a break may be found before a return. So instead of checking for that,
	// I'll just not take this loop body in consideration.
}

/*======================
 Return
======================*/

void USAP_ReturnAnalysis::Analyse(UAST_Return* Return)
{
	// Mark that we reached the return
	PathHasReturn = true;

	// Check return type
	if (IsInVoidFunction())
	{
		// No return expression in void function is valid
		if (!Return->ReturnExpression) return;

		ThrowError(" A void function \"" + CurrentFunction->FunctionData.FunctionName
			+ "\" has a return statement that returns a value.");
		return;
	}
	
	// No return expression in non-void function
	if (!Return->ReturnExpression)
	{
		ThrowError("A non-void function \"" + CurrentFunction->FunctionData.FunctionName
			+ "\" has no return value.");
		return;
	}


	FExpressionReturn ExpressionReturn = GetSymbolTable()->ExpressionReturns[Return->ReturnExpression];
	// Incorrect type returned
	if (ExpressionReturn.ReturnType != CurrentFunction->FunctionData.ReturnType)
	{
		ThrowError("Function \"" + CurrentFunction->FunctionData.FunctionName
			+ "\" returns a wrong type in a return statement. Cannot convert from \"" 
			+ ExpressionReturn.ReturnType +"\" to \"" + CurrentFunction->FunctionData.ReturnType + "\".");
	}

	// Returning a type instead of value
	if (!ExpressionReturn.ReturnsValue())
	{
		ThrowError("Returning a type in function \"" + CurrentFunction->FunctionData.FunctionName + "\" is not allowed.");
	}
		
	
}