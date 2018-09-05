// Fill out your copyright notice in the Description page of Project Settings.

#include "SAP_ConverterAnalysis.h"
#include "Interpreter/SemanticAnalysis/SymbolTable.h"


void USAP_ConverterAnalysis::StartAnalysis(UAST_Node* Root)
{
	for (auto currentPair : GetSymbolTable()->FunctionIDs)
	{
		CurrentClass = currentPair.Key.ClassDefinition;
		AnalyseFunction(currentPair.Value);
	}
}

void USAP_ConverterAnalysis::AnalyseFunction(UAST_FunctionDefinition* Function)
{
	// If function name does not start with "convert" then it is not a converter
	if (!Function->FunctionData.FunctionName.StartsWith("convert")) return;

	// If ther is no current class, this converter is defined in global scope
	if (!CurrentClass)
	{
		ThrowError("Converter functions cannot be defined in global scope.");
		return;
	}

	// Converters must be static
	if (!Function->FunctionData.IsStatic)
	{
		ThrowError("Converter functions must be static.");
		return;
	}

	// Coverter must have only one argument
	if (Function->FunctionData.ParameterData.Num() != 1)
	{
		ThrowError("Converter functions can have only 1 argument.");
		return;
	}

	// Owning class and parameter must be of same type
	if (CurrentClass->Name != Function->FunctionData.ParameterData[0].Type)
	{
		ThrowError("Argument of converter is \"" + Function->FunctionData.ParameterData[0].Type
			+ "\", expected \"" + CurrentClass->Name + "\".");
		return;
	}

	// Return type and name type must match
	FString NameType = Function->FunctionData.FunctionName;
	NameType.RemoveFromStart("convert ");
	NameType.RemoveFromStart("auto ");
	{
		if (Function->FunctionData.ReturnType != NameType)
		{
			ThrowError("Return type and type in converter name must match.");
			return;
		}
	}

	// Check for duplicate conversions
	TSet<FString>* ConvertedTypes = StoredConverters.Find(CurrentClass->Name);
	if (ConvertedTypes && ConvertedTypes->Contains(NameType))
	{
		ThrowError("Conversion from \"" + CurrentClass->Name + "\" to \"" + NameType + "\" already deined.");
		return;
	}

	// Store conveter
	StoredConverters.FindOrAdd(CurrentClass->Name).Add(NameType);
}
