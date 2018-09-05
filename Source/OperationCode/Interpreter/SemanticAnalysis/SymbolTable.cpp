// Fill out your copyright notice in the Description page of Project Settings.

#include "SymbolTable.h"
#include "Interpreter/Parser/AST/Definition/AST_FunctionDefinition.h"

FString USymbolTable::DebugPrintFunctions()
{
	FString result;
	return result;
}


bool USymbolTable::IsChildOfByName(FString child, FString parent) const 
{
	UAST_ClassDefinition*const* ChildClass = ClassNames.Find(child);
	if (!ChildClass) return false;

	UAST_ClassDefinition*const* ParentClass = ClassNames.Find(parent);
	if (!ParentClass) return false;

	return IsChildOf(*ChildClass, *ParentClass);
}

bool USymbolTable::IsChildOf(UAST_ClassDefinition* child, UAST_ClassDefinition* parent) const
{
	if (!child || !parent) return false;

	while (child)
	{
		if (child == parent) return true;

		child = ClassInheritance[child];
	}

	return false;
}


EFunctionMatching USymbolTable::GetFunctionMatch(UAST_FunctionCall* FunctionCall, FFunctionSignature signature, FString ElementType)
{
	if (FunctionCall->FunctionName != signature.FunctionName) return EFunctionMatching::NoMatch;
	if (FunctionCall->Arguments.Num() != signature.ParameterSignatures.Num()) return EFunctionMatching::NoMatch;

	EFunctionMatching currentMatchLevel = EFunctionMatching::ExactMatch;
	for (int i = 0; i < FunctionCall->Arguments.Num(); ++i)
	{
		FExpressionReturn* argumentReturn = ExpressionReturns.Find(FunctionCall->Arguments[i]);
		
		if (!argumentReturn) return EFunctionMatching::NoMatch;

		// Change the type from element type to given one
		if (signature.ParameterSignatures[i].Type == "element type") signature.ParameterSignatures[i].Type = ElementType;

		if (argumentReturn->ReturnType == signature.ParameterSignatures[i].Type 
			&& argumentReturn->ReturnsArray() == signature.ParameterSignatures[i].IsArray) continue;

		// Can only convert types if none of the arguments is an array
		if (!argumentReturn->ReturnsArray() && !signature.ParameterSignatures[i].IsArray
			&& CanConvertTypes(argumentReturn->ReturnType, signature.ParameterSignatures[i].Type))
		{
			currentMatchLevel = EFunctionMatching::WithConversion;
			continue;
		}

		return EFunctionMatching::NoMatch;
	}

	return currentMatchLevel;
}

TArray<UAST_FunctionDefinition*> USymbolTable::GetFunctionDefinitions(UAST_FunctionCall* FunctionCall, UAST_ClassDefinition* OwningClass, FString elementType, bool ReturnOnFirstMatch)
{
	TArray<UAST_FunctionDefinition*> ValidDefinitions;

	// If there is no owning class, function is called from global scope
	if (!OwningClass)
	{
		FStaticFunctions* StaticFun = StaticFunctions.Find("");
		if (!StaticFun) return ValidDefinitions;

		for (UAST_FunctionDefinition* FunDef : StaticFun->Functions)
		{
			EFunctionMatching FunctionMatch = GetFunctionMatch(FunctionCall, FunDef->FunctionData.GetSignature(), elementType);

			switch (FunctionMatch)
			{
			case EFunctionMatching::NoMatch:
				continue;
				break;

			case EFunctionMatching::WithConversion:
				ValidDefinitions.Add(FunDef);
				if (ReturnOnFirstMatch) return ValidDefinitions;
				break;

			case EFunctionMatching::ExactMatch:
				ValidDefinitions.Empty();
				ValidDefinitions.Add(FunDef);
				return ValidDefinitions;

				break;
			default:
				break;
			}
		}
		return ValidDefinitions;
	}

	// In class
	while (OwningClass)
	{
		for (UAST_FunctionDefinition* currentFunction : OwningClass->FunctionDefinitions)
		{
			EFunctionMatching FunctionMatch = GetFunctionMatch(FunctionCall, currentFunction->FunctionData.GetSignature(), elementType);

			switch (FunctionMatch)
			{
			case EFunctionMatching::NoMatch:
				continue;
				break;

			case EFunctionMatching::WithConversion:
				ValidDefinitions.Add(currentFunction);
				if (ReturnOnFirstMatch) return ValidDefinitions;
				break;

			case EFunctionMatching::ExactMatch:
				ValidDefinitions.Empty();
				ValidDefinitions.Add(currentFunction);
				return ValidDefinitions;

				break;
			default:
				break;
			}
		}
		// Next parent
		OwningClass = ClassInheritance[OwningClass];
	}

	return ValidDefinitions;
}

UAST_FunctionDefinition* USymbolTable::GetOverloadedOperator(FFunctionSignature Signature)
{
	// Special case if we are assigning arrays
	FFunctionSignature arraySig;
	arraySig.FunctionName = "operator =";
	arraySig.ParameterSignatures.Add(FParamSignature("element type", true));
	arraySig.ParameterSignatures.Add(FParamSignature("element type", true));

	if (arraySig == Signature) return FunctionIDs[FFunctionID(arraySig, ClassNames["array"])];

	// first check if there is a direct match
	FFunctionID* funId = Operators.Find(Signature);
	if (funId) return FunctionIDs[*funId];

	// Find the correct operator with conversions
	for (auto it = Operators.CreateConstIterator(); it; ++it)
	{
		UAST_FunctionDefinition* funDef = FunctionIDs[it.Value()];
		if (Signature.FunctionName != it.Key().FunctionName) continue;
		if (!DoParameterTypesMatch(funDef, Signature)) continue;

		return funDef;
	}

	return GetSpecialOperator(Signature);
}


bool USymbolTable::CanConvertTypes(FString From, FString To)
{
	// Check if these are valid types
	UAST_ClassDefinition** FromClass = ClassNames.Find(From);
	if (!FromClass) return false;

	UAST_ClassDefinition** ToClass = ClassNames.Find(To);
	if (!ToClass) return false;

	if (IsChildOf(*FromClass, *ToClass)) return true;

	return GetImplicitConverter(*FromClass, *ToClass) != nullptr;
	
}

UAST_FunctionDefinition* USymbolTable::GetImplicitConverterByName(FString From, FString To)
{
	UAST_ClassDefinition** fromClass = ClassNames.Find(From);
	if (!fromClass) return nullptr;

	UAST_ClassDefinition** ToClass = ClassNames.Find(To);
	if (!ToClass) return nullptr;

	return GetImplicitConverter(*fromClass, *ToClass);
}

UAST_FunctionDefinition* USymbolTable::GetImplicitConverter(UAST_ClassDefinition* From, UAST_ClassDefinition* To)
{
	if (!From || !To) return nullptr;
	TArray<FParamSignature> paramSig;
	paramSig.Add(FParamSignature(From->Name, false));
	FFunctionSignature sig = FFunctionSignature("convert auto " + To->Name, paramSig);

	UAST_FunctionDefinition** result = FunctionIDs.Find(FFunctionID(sig, From));
	if (!result) return nullptr;
	return *result;
}

UAST_FunctionDefinition* USymbolTable::GetExplicitConverterByName(FString From, FString To)
{
	UAST_ClassDefinition** fromClass = ClassNames.Find(From);
	if (!fromClass) return nullptr;

	UAST_ClassDefinition** ToClass = ClassNames.Find(To);
	if (!ToClass) return nullptr;

	return GetExplicitConverter(*fromClass, *ToClass);
}

UAST_FunctionDefinition* USymbolTable::GetExplicitConverter(UAST_ClassDefinition* From, UAST_ClassDefinition* To)
{
	if (!From || !To) return nullptr;
	TArray<FParamSignature> paramSig;
	paramSig.Add(FParamSignature(From->Name, false));
	FFunctionSignature sig = FFunctionSignature("convert " + To->Name, paramSig);

	UAST_FunctionDefinition** result = FunctionIDs.Find(FFunctionID(sig, From));
	if (!result) return nullptr;
	return *result;
}




bool USymbolTable::IsInstanceUnique(UAST_ClassDefinition* ClassDefinition)
{
	return IsChildOf(ClassDefinition, ClassNames["Object"]);
}

bool USymbolTable::IsInstanceUniqueByName(FString ClassDefinitionName)
{
	UAST_ClassDefinition** classDef = ClassNames.Find(ClassDefinitionName);
	if (!classDef) return false;

	return IsInstanceUnique(*classDef);
}



bool USymbolTable::DoParameterTypesMatch(UAST_FunctionDefinition* functionDefinition, FFunctionSignature signature)
{
	if (functionDefinition->FunctionData.ParameterData.Num() != signature.ParameterSignatures.Num()) return false;

	for (int i = 0; i < signature.ParameterSignatures.Num(); ++i)
	{
		FParameterData currentParamData = functionDefinition->FunctionData.ParameterData[i];

		if (currentParamData.IsPassByReference && !currentParamData.IsConst)
		{
			// If parameter is pass by reference and is not const, the it has to be an exact match.
			if (currentParamData.Type != signature.ParameterSignatures[i].Type) return false;
		}
		else
		{
			// Check if implicit conversion exists.
			if (!CanConvertTypes(signature.ParameterSignatures[i].Type, currentParamData.Type)) return false;
		}
	}

	return true;
}

UAST_FunctionDefinition* USymbolTable::GetConstructor(FString className, TArray<FParamSignature> paramSig)
{
	UAST_ClassDefinition** ClassDef = ClassNames.Find(className);
	if (!ClassDef) return nullptr;
	FConstructors* constr = Constructors.Find(*ClassDef);
	if (!constr) return nullptr;
	FFunctionSignature sig;
	sig.FunctionName = "constructor";
	sig.ParameterSignatures = paramSig;

	for (UAST_FunctionDefinition* currentFunDef : constr->constructors)
	{
		if (DoParameterTypesMatch(currentFunDef, sig)) return currentFunDef;
	}
	return nullptr;
}





UAST_FunctionDefinition* USymbolTable::GetSpecialOperator(FFunctionSignature signature)
{
	if (signature.ParameterSignatures.Num() != 2) return nullptr;

	if (signature.FunctionName == "operator =")
	{
		FString TopParentName = IsInstanceUniqueByName(signature.ParameterSignatures[0].Type) ? "object" : "class";
		if (!CanConvertTypes(signature.ParameterSignatures[1].Type, signature.ParameterSignatures[0].Type)) return nullptr;

		FFunctionSignature sig;
		sig.FunctionName = "operator =";
		sig.ParameterSignatures.Add(FParamSignature(TopParentName, false));
		sig.ParameterSignatures.Add(FParamSignature(TopParentName, false));
		return FunctionIDs[FFunctionID(sig, ClassNames[TopParentName])];
	}

	if (signature.FunctionName == "operator ==")
	{
		if (!IsInstanceUniqueByName(signature.ParameterSignatures[0].Type) || !IsInstanceUniqueByName(signature.ParameterSignatures[1].Type)) return nullptr;
	
		FFunctionSignature sig;
		sig.FunctionName = "operator ==";
		sig.ParameterSignatures.Add(FParamSignature("object", false));
		sig.ParameterSignatures.Add(FParamSignature("object", false));
		return FunctionIDs[FFunctionID(sig, ClassNames["object"])];
	}

	return nullptr;
}



