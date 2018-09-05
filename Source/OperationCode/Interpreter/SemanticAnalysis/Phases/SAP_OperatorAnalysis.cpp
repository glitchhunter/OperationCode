// Fill out your copyright notice in the Description page of Project Settings.

#include "SAP_OperatorAnalysis.h"
#include "Interpreter/SemanticAnalysis/SymbolTable.h"

#include "Interpreter/Parser/AST/AST_Basic.h"
#include "Interpreter/Parser/AST/AST_Main.h"
#include "Interpreter/Parser/AST/Definition/AST_ClassDefinition.h"
#include "Interpreter/Parser/AST/Definition/AST_FunctionDefinition.h"

USAP_OperatorAnalysis::USAP_OperatorAnalysis()
{
	UnaryOperatorReturns.Add("+", false);
	UnaryOperatorReturns.Add("-", false);
	UnaryOperatorReturns.Add("!", true);

	UnaryOperatorReturns.Add("++ (suffix)", false);
	UnaryOperatorReturns.Add("++ (prefix)", false);
	UnaryOperatorReturns.Add("-- (suffix)", false);
	UnaryOperatorReturns.Add("-- (prefix)", false);

	BinaryOperatorReturns.Add("+", false);
	BinaryOperatorReturns.Add("-", false);
	BinaryOperatorReturns.Add("*", false);
	BinaryOperatorReturns.Add("/", false);
	BinaryOperatorReturns.Add("%", false);

	BinaryOperatorReturns.Add("<", true);
	BinaryOperatorReturns.Add("<=", true);
	BinaryOperatorReturns.Add(">", true);
	BinaryOperatorReturns.Add(">=", true);
	BinaryOperatorReturns.Add("!=", true);
	BinaryOperatorReturns.Add("==", true);
	BinaryOperatorReturns.Add("&&", true);
	BinaryOperatorReturns.Add("||", true);
	BinaryOperatorReturns.Add("=", false);
}

void USAP_OperatorAnalysis::StartAnalysis(UAST_Node* RootNode)
{
	// Loop through all functions
	for (TPair<FFunctionID, UAST_FunctionDefinition*> currentPair : GetSymbolTable()->FunctionIDs)
	{
		FFunctionID currentFunctionID = currentPair.Key;
		// skip non operator overload functions
		if (!currentFunctionID.Signature.FunctionName.StartsWith("operator ", ESearchCase::CaseSensitive)) continue;

		FString operatorName = currentFunctionID.Signature.FunctionName;
		operatorName.RemoveFromStart("operator ");

		// Get forced bool return
		bool ForcedBoolReturn;
		int32 parameterCount = currentFunctionID.Signature.ParameterSignatures.Num();
		switch (parameterCount)
		{
		case 1:
			if (!UnaryOperatorReturns.Contains(operatorName))
			{
				if (BinaryOperatorReturns.Contains(operatorName))
					ThrowError("Operator overload error. \"" + operatorName + "\" does not take 1 argument.");
				else ThrowError("Cannot overload \"" + operatorName + "\".");
				return;
			}
			ForcedBoolReturn = UnaryOperatorReturns[operatorName];
			break;

		case 2:
			if (!BinaryOperatorReturns.Contains(operatorName))
			{
				if (UnaryOperatorReturns.Contains(operatorName))
					ThrowError("Operator overload error. \"" + operatorName + "\" does not take 2 arguments.");
				else ThrowError("Cannot overload \"" + operatorName + "\".");
				return;
			}
			ForcedBoolReturn = BinaryOperatorReturns[operatorName];
			break;

		default:
			if (UnaryOperatorReturns.Contains(operatorName) || BinaryOperatorReturns.Contains(operatorName))
				ThrowError("Cannot overload \"" + operatorName + "\" with " + FString::FromInt(parameterCount) + " arguments.");
			else ThrowError("Cannot overload operator \"" + operatorName + "\".");
			return;
			break;
		}

		// Check return type
		if (ForcedBoolReturn && currentPair.Value->FunctionData.ReturnType != "bool")
		{
			ThrowError("Functions that overload operator \"" + operatorName + "\" must return a bool.");
			return;
		}

		// Is function declared inside a proper class (skip array)
		if (currentFunctionID.ClassDefinition->Name != "array" && !IsInProperClass(currentFunctionID))
		{
			ThrowError("When overloading operators, function must be declared inside a class that is used as an argument.");
			return;
		}

		// Is function static
		if (!currentPair.Value->FunctionData.IsStatic)
		{
			ThrowError("Functions that overload operators must be static.");
			return;
		}

		// Check for duplicates
		FFunctionSignature overloadSignature = currentFunctionID.Signature;

		// Only overloads with two arguments can be duplicates
		if (overloadSignature.ParameterSignatures.Num() == 2)
		{
			FFunctionID* funID = GetSymbolTable()->Operators.Find(overloadSignature);
			if (funID)
			{
				ThrowError("Operator overload for operator \"" + operatorName + "\" with arguments of types "
					+ overloadSignature.ParameterSignatures[0].Type + " and " + overloadSignature.ParameterSignatures[1].Type
					+ " defined in both classes.");
				return;
			}
		}

		// Store
		GetSymbolTable()->Operators.Add(overloadSignature, currentPair.Key);
	}
}

bool USAP_OperatorAnalysis::IsInProperClass(FFunctionID FunctionID)
{
	if (!FunctionID.ClassDefinition) return false;

	for (FParamSignature currentParam : FunctionID.Signature.ParameterSignatures)
	{
		if (FunctionID.ClassDefinition->Name == currentParam.Type) return true;
	}
	return false;
}