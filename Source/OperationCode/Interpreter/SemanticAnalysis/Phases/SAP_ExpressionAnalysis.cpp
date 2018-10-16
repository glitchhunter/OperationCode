// Fill out your copyright notice in the Description page of Project Settings.

#include "SAP_ExpressionAnalysis.h"
#include "Interpreter/SemanticAnalysis/Phases/SemanticAnalysisPhase.h"
#include "Interpreter/SemanticAnalysis/SymbolTable.h"
#include "Interpreter/SemanticAnalysis/ExpressionReturns.h"

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
#include "Interpreter/Parser/AST/FlowControl/Loops/AST_For.h"
#include "Interpreter/Parser/AST/FlowControl/Loops/AST_While.h"
#include "Interpreter/Parser/AST/FlowControl/AST_If.h"

#include "Interpreter/Parser/AST/Expressions/Operators/AST_Operator.h"
#include "Interpreter/Parser/AST/Expressions/Operators/OneArgument/AST_OneArgument.h"
#include "Interpreter/Parser/AST/Expressions/Operators/TwoArguments/AST_TwoArguments.h"
#include "Interpreter/Parser/AST/Expressions/Operators/TwoArguments/AST_MemberAccess.h"
#include "Interpreter/Parser/AST/Expressions/AST_Type.h"




void USAP_ExpressionAnalysis::AddStepToPath(UAST_Node* Step)
{
	Path.Add(FExpressionPath(Step));
}

void USAP_ExpressionAnalysis::RemoveLastStep()
{
	Path.Pop();
}

void USAP_ExpressionAnalysis::AddFunctionToLastStep(UAST_FunctionDefinition* FunctionDefinition) 
{
	if (Path.Num() <= 0) return;
	Path.Top().Functions.Add(FunctionDefinition);
}

void USAP_ExpressionAnalysis::AddVariableToLastStep(FString VariableName, FExpressionReturn returnData)
{
	if (Path.Num() <= 0) return;
	Path.Top().Variables.Add(VariableName, returnData);
}

bool USAP_ExpressionAnalysis::VariableExistsInLastStep(FString VariableName)
{
	if (Path.Num() <= 0) return false;

	return Path.Top().Variables.Contains(VariableName);
}


/*======================
 Basic
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_Basic* Basic)
{
	AddStepToPath(Basic);
	AnalyseChildren(Basic);
	RemoveLastStep();
}


/*======================
 Main
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_Main* Main)
{
	AddStepToPath(Main);
	AnalyseChildren(Main);
	RemoveLastStep();
}


/*======================
 Class definition
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_ClassDefinition* ClassDefinition)
{
	AddStepToPath(ClassDefinition);
	AnalyseChildren(ClassDefinition);
	RemoveLastStep();
}

/*======================
 Function definition
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_FunctionDefinition* FunctionDefinition)
{
	// Fuinction definition belongs to its parent
	AddFunctionToLastStep(FunctionDefinition);

	// Arguments and function body belongs to function
	AddStepToPath(FunctionDefinition);

	// Add arguments as variables
	TSet<FString> ParameterNames;
	for (FParameterData currentParam : FunctionDefinition->FunctionData.ParameterData)
	{
		if (currentParam.Type != "element type" && !GetSymbolTable()->ClassNames.Contains(currentParam.Type))
		{
			ThrowError("Unknown type \"" + currentParam.Type + "\" detected as argument \""
				+ currentParam.Name + "\" in function \"" + FunctionDefinition->FunctionData.FunctionName + "\".");
			return;
		}

		// Check if arguments have duplicate names
		if (ParameterNames.Contains(currentParam.Name))
		{
			ThrowError("Function " + FunctionDefinition->FunctionData.FunctionName + " has multiple arguments with same name: " + currentParam.Name + ".");
			continue;
		}
		ParameterNames.Add(currentParam.Name);
		EReturnMode returnMode = currentParam.IsArray ? EReturnMode::Array : EReturnMode::Value;
		AddVariableToLastStep(currentParam.Name, FExpressionReturn(currentParam.Type, returnMode));
	}

	if (FunctionDefinition->FunctionData.ReturnType != "element type" 
		&& FunctionDefinition->FunctionData.ReturnType != "void"
		&& !GetSymbolTable()->ClassNames.Contains(FunctionDefinition->FunctionData.ReturnType))
	{
		ThrowError("Unknown return type \"" + FunctionDefinition->FunctionData.ReturnType + "\" in function \"" + FunctionDefinition->FunctionData.FunctionName + "\".");
		return;
	}

	// Procede to scope, if valid
	if (FunctionDefinition->Scope) FunctionDefinition->Scope->Analyse(this);

	// Remove from path
	RemoveLastStep();
}


/*======================
 Variable definition
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_VariableDefinition* VariableDefinition)
{
	if (!GetSymbolTable()->ClassNames.Contains(VariableDefinition->Type))
	{
		ThrowError("Unknown type \"" + VariableDefinition->Type + "\" detected in variable definition named \"" + VariableDefinition->Name + "\".");
		return;
	}

	if (VariableExistsInLastStep(VariableDefinition->Name))
	{
		ThrowError("Variable " + VariableDefinition->Name + " redefined.");
	}
	EReturnMode returnMode = VariableDefinition->IsArray ? EReturnMode::Array : EReturnMode::Value;
	AddVariableToLastStep(VariableDefinition->Name, FExpressionReturn(VariableDefinition->Type, returnMode));

	// Analyse init expression if it exists
	if (VariableDefinition->InitExpression)
	{
		VariableDefinition->InitExpression->Analyse(this);

		FExpressionReturn* expReturn = GetSymbolTable()->ExpressionReturns.Find(VariableDefinition->InitExpression);
		if (expReturn)
		{
			if (expReturn->ReturnsType())
			{
				ThrowError("Cannot store a type in a variable.");
				return;
			}
			
			if (!GetSymbolTable()->CanConvertTypes(expReturn->ReturnType, VariableDefinition->Type))
			{
				ThrowError("Cannot convert from \"" + expReturn->ReturnType + "\" to \""
					+ VariableDefinition->Type + "\".");
				return;
			}

			if (VariableDefinition->IsArray != expReturn->ReturnsArray())
			{
				ThrowError("Only arrays are compatible with other arrays.");
				return;
			}
		}
	}

}


/*======================
 Do while
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_DoWhile* DoWhile)
{
	// Add step
	AddStepToPath(DoWhile);

	// Analyse condition
	DoWhile->Condition->Analyse(this);

	// Check if condition returns a bool
	FExpressionReturn* conditionData = GetSymbolTable()->ExpressionReturns.Find(DoWhile->Condition);
	if (!conditionData) return;

	if (!(GetSymbolTable()->CanConvertTypes(conditionData->ReturnType, "bool") && conditionData->ReturnsValue()))
	{
		ThrowError("Expected a bool value in do while condition, found " + conditionData->AsString() + " instead.");
	}

	// Analyse loop body
	DoWhile->Body->Analyse(this);

	// Remove from path
	RemoveLastStep();
}


/*======================
 For
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_For* For)
{
	// Add step
	AddStepToPath(For);

	// Analyse initialization
	For->Initialization->Analyse(this);

	// Analyse condition
	For->Condition->Analyse(this);

	// Check if condition returns a bool
	FExpressionReturn* conditionData = GetSymbolTable()->ExpressionReturns.Find(For->Condition);
	if (!conditionData) return;

	if (!(GetSymbolTable()->CanConvertTypes(conditionData->ReturnType, "bool") && conditionData->ReturnsValue()))
	{
		ThrowError("Expected a bool value in for condition, found " + conditionData->AsString() + " instead.");
	}

	// Analyse loop update
	For->Update->Analyse(this);

	// Analyse loop body
	For->Body->Analyse(this);

	// Remove from path
	RemoveLastStep();
}


/*======================
 If
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_If* If)
{
	// Add step
	AddStepToPath(If);

	// Analyse condition
	If->Condition->Analyse(this);

	// Check if condition returns a bool
	FExpressionReturn* conditionData = GetSymbolTable()->ExpressionReturns.Find(If->Condition);
	if (!conditionData) return;

	if (!(GetSymbolTable()->CanConvertTypes(conditionData->ReturnType, "bool") && conditionData->ReturnsValue()))
	{
		ThrowError("Expected a bool value in if condition, found " + conditionData->AsString() + " instead.");
	}

	// Analyse true branch
	If->TrueBranch->Analyse(this);

	// Analyse false branch, if it exists
	if (If->FalseBranch)
	{
		If->FalseBranch->Analyse(this);
	}

	// Remove from path
	RemoveLastStep();
}


/*======================
 While
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_While* While)
{
	// Add step
	AddStepToPath(While);

	// Analyse condition
	While->Condition->Analyse(this);

	// Check if condition returns a bool
	FExpressionReturn* conditionData = GetSymbolTable()->ExpressionReturns.Find(While->Condition);
	if (!conditionData) return;

	if (!(GetSymbolTable()->CanConvertTypes(conditionData->ReturnType, "bool") && conditionData->ReturnsValue()))
	{
		ThrowError("Expected a bool value in while condition, found " + conditionData->AsString() + " instead.");
	}

	// Analyse body
	While->Body->Analyse(this);

	// Remove from path
	RemoveLastStep();
}


/*======================
 Function call
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_FunctionCall* FunctionCall)
{
	// Localy store caller
	FExpressionReturn localCaller = Caller;
	Caller.Clear();

	// Store potentialy valid definitions
	TSet<UAST_FunctionDefinition*> PotentialDefinitions;
	UAST_FunctionDefinition* Result = nullptr;

	// Argument types
	TArray<FString> ArgumentTypes;

	// Analyse arguments
	for (UAST_Expression* currentExpression : FunctionCall->Arguments)
	{
		currentExpression->Analyse(this);
		FExpressionReturn* argReturn = GetSymbolTable()->ExpressionReturns.Find(currentExpression);
		if (!argReturn) return;
		if (argReturn->ReturnsType())
		{
			ThrowError("Cannot pass a type as an argument for function call " + FunctionCall->FunctionName + ".");
		}
		ArgumentTypes.Add(argReturn->ReturnType);
	}


	// If caller is a type
	if (localCaller.ReturnsType())
	{
		FStaticFunctions* statFun = GetSymbolTable()->StaticFunctions.Find(localCaller.ReturnType);
		if (!statFun)
		{
			ThrowError("Class of type \"" + localCaller.ReturnType + "\" does not have a static function named \"" + FunctionCall->FunctionName + "\".");
			return;
		}

		for (UAST_FunctionDefinition* FunDef : statFun->Functions)
		{
			// If signatures match, this is the correct function
			if (GetSymbolTable()->GetFunctionMatch(FunctionCall, FunDef->FunctionData.GetSignature(), "") != EFunctionMatching::NoMatch)
			{
				// Found Function definition
				GetSymbolTable()->StaticFunctionCalls.Add(FunctionCall, FunDef);
				EReturnMode returnMode = FunDef->FunctionData.ReturnsArray ? EReturnMode::Array : EReturnMode::Value;
				GetSymbolTable()->ExpressionReturns.Add(FunctionCall, FExpressionReturn(FunDef->FunctionData.ReturnType, returnMode));
				return;
			}
		}
		// No matching functions
		ThrowError("Class of type \"" + localCaller.ReturnType + "\" does not have a static function named \"" + FunctionCall->FunctionName + "\".");
		return;
	}




	// Implicit caller
	if (localCaller.IsClear())
	{
		bool IsConstructor = false;
		// Special case if the function is a constructor
		FString funName = FunctionCall->FunctionName;
		UAST_ClassDefinition** constructorClass = GetSymbolTable()->ClassNames.Find(funName);
		if (constructorClass)
		{
			IsConstructor = true;
			PotentialDefinitions.Append(GetSymbolTable()->GetFunctionDefinitions(FunctionCall, *constructorClass, "", false));


			if (PotentialDefinitions.Num() == 1) 
			{
				GetSymbolTable()->ExpressionReturns.Add(FunctionCall, FExpressionReturn(funName, EReturnMode::Value));
				return;
			}
			else if (PotentialDefinitions.Num() == 0)
			{
				if (FunctionCall->Arguments.Num() == 0)
				{
					// Default constructor
					GetSymbolTable()->ExpressionReturns.Add(FunctionCall, FExpressionReturn(funName, EReturnMode::Value));
					return;
				}
				ThrowError("No suitable constructor found for " + funName + ".");
				return;
			}
			else
			{
				ThrowError("Ambiguous call for " + funName + " constructor.");
				return;
			}



		}
		else
		{
			// Check for top owner
			UValue* TopOwner = GetSymbolTable()->TopOwner;
			if (TopOwner)
			{
				FString classType = TopOwner->Type;
				TArray<UAST_FunctionDefinition*> results = GetFunctionDefinitionsWithExplicitCaller(classType, classType, FunctionCall);
				if (results.Num() == 1)
				{
					Result = results[0];

					// This is code from below. Just adding some spagetti
					EReturnMode returnMode = Result->FunctionData.ReturnsArray ? EReturnMode::Array : EReturnMode::Value;
					FString returnType = Result->FunctionData.ReturnType == "element type" ? localCaller.ReturnType : Result->FunctionData.ReturnType;
					GetSymbolTable()->ExpressionReturns.Add(FunctionCall, FExpressionReturn(returnType, returnMode));
					GetSymbolTable()->TopOwnedFunctionCalls.Add(FunctionCall);
					return;
				}
			}






			// Find matching function definitions in global scope
			PotentialDefinitions.Append(GetSymbolTable()->GetFunctionDefinitions(FunctionCall, nullptr, "", false));
		}

		// If there are no matching definitions
		if (PotentialDefinitions.Num() <= 0)
		{
			ThrowError("Call for function \"" + FunctionCall->FunctionName + "\" does not match any function definition");
			return;
		}

		// Iterate up through the path until we find a valid match
		for (int i = Path.Num() - 1; i >= 0; --i)
		{
			TSet<UAST_FunctionDefinition*> ValidDefinitions = PotentialDefinitions.Intersect(Path[i].Functions);
			if (ValidDefinitions.Num() <= 0) continue;
			if (ValidDefinitions.Num() == 1)
			{
				Result = ValidDefinitions.Array()[0];
				break;
			}
			if (ValidDefinitions.Num() > 1)
			{
				ThrowError("Ambiguous call for \"" + FunctionCall->FunctionName + "\" function. Multiple matching definitions found.");
				return;
			}
		}
	}
	else
	{
		FString callerName = localCaller.ReturnsArray() ? "array" : localCaller.ReturnType;
		UAST_ClassDefinition** callerClass = GetSymbolTable()->ClassNames.Find(callerName);

		TArray<UAST_FunctionDefinition*> results = GetFunctionDefinitionsWithExplicitCaller(callerName, localCaller.ReturnType, FunctionCall);
		if (results.Num() > 1)
		{
			ThrowError("Ambiguous call for \"" + FunctionCall->FunctionName + "\" function. Multiple matching definitions found.");
			return;
		}
		else if (results.Num() <= 0)
		{
			ThrowError("Call for function \"" + FunctionCall->FunctionName + "\" does not match any function definition");
			return;
		}
		Result = results[0];


		// This is turned into a function. Leaving it here in case function does not work
		/*
		// Explicit caller
		FString callerName = localCaller.ReturnsArray() ? "array" : localCaller.ReturnType;
		UAST_ClassDefinition** callerClass = GetSymbolTable()->ClassNames.Find(callerName);
		if (!callerClass) return;
		PotentialDefinitions.Append(GetSymbolTable()->GetFunctionDefinitions(FunctionCall, *callerClass, localCaller.ReturnType, false));

		// If there are no matching definitions
		if (PotentialDefinitions.Num() <= 0)
		{
			ThrowError("Call for function \"" + FunctionCall->FunctionName + "\" does not match any function definition");
			return;
		}

		// Iterate through inheritance chain
		UAST_ClassDefinition** temp = GetSymbolTable()->ClassNames.Find(callerName);
		if (!temp) return;
		UAST_ClassDefinition* CurrentClass = *temp;
		while (CurrentClass)
		{
			TSet<UAST_FunctionDefinition*> currentFunctionDefinitions;
			currentFunctionDefinitions.Append(CurrentClass->FunctionDefinitions);
			TSet<UAST_FunctionDefinition*> ValidDefinitions = PotentialDefinitions.Intersect(currentFunctionDefinitions);
			if (ValidDefinitions.Num() <= 0)
			{
				CurrentClass = GetSymbolTable()->ClassInheritance[CurrentClass];
				continue;
			}
			if (ValidDefinitions.Num() == 1)
			{
				Result = ValidDefinitions.Array()[0];
				break;
			}
			if (ValidDefinitions.Num() > 1)
			{
				ThrowError("Ambiguous call for \"" + FunctionCall->FunctionName + "\" function. Multiple matching definitions found.");
				return;
			}
		}
		*/
	}





	if (!Result)
	{
		// No function definition found
		ThrowError("Undefined function found: " + FunctionCall->FunctionName + ".");
		return;
	}

	// Static check
	if (Result->FunctionData.IsStatic && localCaller.ReturnType != "")
	{
		ThrowError("Function \"" + FunctionCall->FunctionName + "\" is marked as static, but is not being called from a type.");
	}



	EReturnMode returnMode = Result->FunctionData.ReturnsArray ? EReturnMode::Array : EReturnMode::Value;
	FString returnType = Result->FunctionData.ReturnType == "element type" ? localCaller.ReturnType : Result->FunctionData.ReturnType;
	GetSymbolTable()->ExpressionReturns.Add(FunctionCall, FExpressionReturn(returnType, returnMode));
}


/*======================
 Variable call
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_VariableCall* VariableCall)
{
	// Localy store caller
	FExpressionReturn localCaller = Caller;
	Caller.Clear();





	// If caller is a type
	if (localCaller.ReturnsType())
	{
		FStaticVariables* statVar = GetSymbolTable()->StaticVariables.Find(localCaller.ReturnType);
		if (!statVar)
		{
			ThrowError("Class of type \"" + localCaller.ReturnType + "\" does not have a static variable named \"" + VariableCall->VariableName + "\".");
			return;
		}

		for (UAST_VariableDefinition* varDef : statVar->Variables)
		{
			// If names match, the correct variable exists
			if (varDef->Name == VariableCall->VariableName)
			{
				// Link this static variable calll to variable definition
				GetSymbolTable()->StaticVariableCalls.Add(VariableCall, varDef);
				EReturnMode returnMode = varDef->IsArray ? EReturnMode::Array : EReturnMode::Value;
				GetSymbolTable()->ExpressionReturns.Add(VariableCall, FExpressionReturn(varDef->Type, returnMode));
				return;
			}
		}

		// No matching variables
		ThrowError("Class of type \"" + localCaller.ReturnType + "\" does not have a static variable named \"" + VariableCall->VariableName + "\".");
		return;
	}




	// Implicit caller
	if (localCaller.IsClear())
	{
		// Move up the path until we find the definition
		for (int i = Path.Num() - 1; i >= 0; --i)
		{
			FExpressionReturn* expReturn = Path[i].Variables.Find(VariableCall->VariableName);
			if (!expReturn) continue;

			GetSymbolTable()->ExpressionReturns.Add(VariableCall, *expReturn);
			return;

		}

		// Check for top owner
		if (GetSymbolTable()->TopOwner)
		{
			UAST_ClassDefinition** classDefinition = GetSymbolTable()->ClassNames.Find(GetSymbolTable()->TopOwner->Type);
			if (!classDefinition) return;

			UAST_ClassDefinition* currentClass = *classDefinition;
			while (currentClass)
			{
				for (UAST_VariableDefinition* currentVarDefinition : currentClass->VariableDefinitions)
				{
					if (currentVarDefinition->Name != VariableCall->VariableName) continue;

					// Found variable definition
					EReturnMode returnMode = currentVarDefinition->IsArray ? EReturnMode::Array : EReturnMode::Value;
					GetSymbolTable()->ExpressionReturns.Add(VariableCall, FExpressionReturn(currentVarDefinition->Type, returnMode));
					GetSymbolTable()->TopOwnedVariableCalls.Add(VariableCall);
					return;
				}
				// Check if variable exists in parent
				currentClass = GetSymbolTable()->ClassInheritance[currentClass];
			}

		}

		// variable undefined
		ThrowError("Unknown variable \"" + VariableCall->VariableName + "\" detected.");
		return;
	}

	// Explicit caller
	UAST_ClassDefinition** classDefinition = GetSymbolTable()->ClassNames.Find(localCaller.ReturnType);
	if (!classDefinition)
	{
		ThrowError("Unknown caller of type \"" + localCaller.ReturnType + "\" calls a variable named \"" + VariableCall->VariableName + "\".");
		return;
	}

	UAST_ClassDefinition* currentClass = *classDefinition;
	while (currentClass)
	{
		for (UAST_VariableDefinition* currentVarDefinition : currentClass->VariableDefinitions)
		{
			if (currentVarDefinition->Name != VariableCall->VariableName) continue;

			// Found variable definition
			EReturnMode returnMode = currentVarDefinition->IsArray ? EReturnMode::Array : EReturnMode::Value;
			GetSymbolTable()->ExpressionReturns.Add(VariableCall, FExpressionReturn(currentVarDefinition->Type, returnMode));
			return;
		}
		// Check if variable exists in parent
		currentClass = GetSymbolTable()->ClassInheritance[currentClass];
	}

	// No variable with that name is defined
	ThrowError("Undefined variable \"" + VariableCall->VariableName + "\" detected.");
}



/*======================
 Bool literal
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_BoolLiteral* BoolLiteral)
{
	GetSymbolTable()->ExpressionReturns.Add(BoolLiteral, FExpressionReturn("bool", EReturnMode::Value));
}


/*======================
 Float literal
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_FloatLiteral* FloatLiteral)
{
	GetSymbolTable()->ExpressionReturns.Add(FloatLiteral, FExpressionReturn("float", EReturnMode::Value));
}


/*======================
 Int literal
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_IntLiteral* IntLiteral)
{
	GetSymbolTable()->ExpressionReturns.Add(IntLiteral, FExpressionReturn("int", EReturnMode::Value));
}


/*======================
 String literal
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_StringLiteral* StringLiteral)
{
	GetSymbolTable()->ExpressionReturns.Add(StringLiteral, FExpressionReturn("string", EReturnMode::Value));
}


/*======================
 Nullptr literal
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_NullptrLiteral* Nullptr)
{
	GetSymbolTable()->ExpressionReturns.Add(Nullptr, FExpressionReturn("object", EReturnMode::Value));
}



/*======================
 Two arguments
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_TwoArguments* TwoArguments)
{
	// Function name based on operator
	FString name = "operator " + TwoArguments->GetDescription();

	// Analyse LHS argument
	TwoArguments->lhs->Analyse(this);
	// Store LHS argument type as class
	FExpressionReturn* lhsReturn = GetSymbolTable()->ExpressionReturns.Find(TwoArguments->lhs);
	if (!lhsReturn) return;
	if (lhsReturn->ReturnsType()) ThrowError("Cannot take a type as an argument.");
	if (lhsReturn->ReturnType == "void") ThrowError("Cannot call functions on void. Try separating code with a ;");
	UAST_ClassDefinition** lhsClass = GetSymbolTable()->ClassNames.Find(lhsReturn->ReturnType);
	if (!lhsClass) return;

	// Analyse RHS argument
	TwoArguments->rhs->Analyse(this);
	// Store RHS argument type
	FExpressionReturn* rhsReturn = GetSymbolTable()->ExpressionReturns.Find(TwoArguments->rhs);
	if (!rhsReturn) return;
	if (rhsReturn->ReturnsType()) ThrowError("Cannot take a type as an argument.");
	if (rhsReturn->ReturnType == "void") ThrowError("Cannot call functions on void. Try separating code with a ;");
	UAST_ClassDefinition** rhsClass = GetSymbolTable()->ClassNames.Find(rhsReturn->ReturnType);
	if (!rhsClass) return;

	// Find in which class (if any) this overload is defined in
	TArray<FParamSignature> paramSig;
	paramSig.Add(FParamSignature(lhsReturn->ReturnType, lhsReturn->ReturnsArray()));
	paramSig.Add(FParamSignature(rhsReturn->ReturnType, lhsReturn->ReturnsArray()));

	// Try to find in lhs type class
	UAST_FunctionDefinition* lhsFound = GetSymbolTable()->GetOverloadedOperator(FFunctionSignature(name, paramSig));
	if (lhsFound)
	{
		EReturnMode returnMode = lhsFound->FunctionData.ReturnsArray ? EReturnMode::Array : EReturnMode::Value;
		GetSymbolTable()->ExpressionReturns.Add(TwoArguments, FExpressionReturn(lhsFound->FunctionData.ReturnType, returnMode));
		return;
	}

	// Try to find in rhs type class
	UAST_FunctionDefinition* rhsFound = GetSymbolTable()->GetOverloadedOperator(FFunctionSignature(name, paramSig));
	if (rhsFound)
	{
		EReturnMode returnMode = rhsFound->FunctionData.ReturnsArray ? EReturnMode::Array : EReturnMode::Value;
		GetSymbolTable()->ExpressionReturns.Add(TwoArguments, FExpressionReturn(rhsFound->FunctionData.ReturnType, returnMode));
		return;
	}

	// Overload not found
	ThrowError("No overload found for " + name + " with arguments of type " + lhsReturn->ReturnType + " and " + rhsReturn->ReturnType + ".");
}


/*======================
 One argument
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_OneArgument* OneArgument)
{
	// Function name based on operator
	FString name = "operator " + OneArgument->GetDescription();

	// Analyse argument
	OneArgument->Argument->Analyse(this);

	// Store argument type as class
	FExpressionReturn* ArgReturn = GetSymbolTable()->ExpressionReturns.Find(OneArgument->Argument);
	if (!ArgReturn) return;
	if (ArgReturn->ReturnsType()) ThrowError("Cannot take a type as an argument.");
	if (ArgReturn->ReturnType == "void") ThrowError("Cannot call functions on void. Try separating code with a ;");
	UAST_ClassDefinition** ArgClass = GetSymbolTable()->ClassNames.Find(ArgReturn->ReturnType);
	if (!ArgClass) return;

	// Find Definition
	TArray<FParamSignature> params;
	params.Add(FParamSignature(ArgReturn->ReturnType, ArgReturn->ReturnsArray()));
	UAST_FunctionDefinition* FunctionDefinition = GetSymbolTable()->GetOverloadedOperator(FFunctionSignature(name, params));

	if (!FunctionDefinition)
	{
		ThrowError("No suitable operator overload found for " + name + " with argument of type " + ArgReturn->ReturnType + ".");
		return;
	}

	GetSymbolTable()->ExpressionReturns.Add(OneArgument, FExpressionReturn(ArgReturn->ReturnType, ArgReturn->ReturnMode));
}

/*======================
 Member access
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_MemberAccess* MemberAccess)
{
	// Get caller
	MemberAccess->lhs->Analyse(this);

	// Store caller type for call
	FExpressionReturn* ExpReturn = GetSymbolTable()->ExpressionReturns.Find(MemberAccess->lhs);
	if (!ExpReturn) return;
	Caller = *ExpReturn;

	// Analyse call
	MemberAccess->rhs->Analyse(this);

	// Reset caller type
	Caller.Clear();

	// Store
	FExpressionReturn* rhsReturn = GetSymbolTable()->ExpressionReturns.Find(MemberAccess->rhs);
	if (!rhsReturn) return;
	GetSymbolTable()->ExpressionReturns.Add(MemberAccess, *rhsReturn);
}


/*======================
 Expression
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_Expression* Expression)
{
	AddStepToPath(Expression);
	AnalyseChildren(Expression);
	RemoveLastStep();
}


/*======================
 Scope
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_Scope* Scope)
{
	AddStepToPath(Scope);
	AnalyseChildren(Scope);
	RemoveLastStep();
}


/*======================
 Return
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_Return* Return)
{
	AnalyseChildren(Return);
}


/*======================
 Type
======================*/

void USAP_ExpressionAnalysis::Analyse(UAST_Type* Type)
{
	GetSymbolTable()->ExpressionReturns.Add(Type, FExpressionReturn(Type->Type, EReturnMode::Type));
}








TArray<UAST_FunctionDefinition*> USAP_ExpressionAnalysis::GetFunctionDefinitionsWithExplicitCaller(FString ClassType, FString ReturnType, UAST_FunctionCall* FunctionCall)
{
	UAST_ClassDefinition** callerClass = GetSymbolTable()->ClassNames.Find(ClassType);
	if (!callerClass) return TArray<UAST_FunctionDefinition*>();
	TSet<UAST_FunctionDefinition*> PotentialDefinitions;
	PotentialDefinitions.Append(GetSymbolTable()->GetFunctionDefinitions(FunctionCall, *callerClass, ReturnType, false));

	// If there are no matching definitions
	if (PotentialDefinitions.Num() <= 0)
	{
		return TArray<UAST_FunctionDefinition*>();
	}

	// Iterate through inheritance chain
	UAST_ClassDefinition* CurrentClass = *callerClass;
	while (CurrentClass)
	{
		TSet<UAST_FunctionDefinition*> currentFunctionDefinitions;
		currentFunctionDefinitions.Append(CurrentClass->FunctionDefinitions);
		TSet<UAST_FunctionDefinition*> ValidDefinitions = PotentialDefinitions.Intersect(currentFunctionDefinitions);
		if (ValidDefinitions.Num() <= 0)
		{
			CurrentClass = GetSymbolTable()->ClassInheritance[CurrentClass];
			continue;
		}

		return ValidDefinitions.Array();
	}
	return TArray<UAST_FunctionDefinition*>();
}
