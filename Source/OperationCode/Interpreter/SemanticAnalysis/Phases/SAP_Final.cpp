// Fill out your copyright notice in the Description page of Project Settings.

#include "SAP_Final.h"
#include "Interpreter/SemanticAnalysis/SymbolTable.h"

void USAP_Final::StartAnalysis(UAST_Node* RootNode)
{
	for (auto it = GetSymbolTable()->FunctionIDs.CreateConstIterator(); it; ++it)
	{
		// Store them separatly for readability
		UAST_ClassDefinition* currentClass = it.Key().ClassDefinition;
		UAST_FunctionDefinition* currentFunction = it.Value();

		// Class Analysis already made sure there is no circular inheritance, so this loop must end at some point
		UAST_ClassDefinition** parent = GetSymbolTable()->ClassInheritance.Find(currentClass);
		while (parent)
		{
			// Check if parent contains a function with the same signature
			UAST_FunctionDefinition** parentFunction = GetSymbolTable()->FunctionIDs.Find(FFunctionID(currentFunction->FunctionData.GetSignature(), *parent));
			if (!parentFunction)
			{
				// Go to next parent
				parent = GetSymbolTable()->ClassInheritance.Find(*parent);
				continue;
			}

			// If parent function is marked as final, then current function cannot overtide it
			if ((*parentFunction)->FunctionData.IsFinal)
			{
				ThrowError("Class " + currentClass->Name + " overrides a function " + currentFunction->FunctionData.FunctionName
					+ " from its parent " + currentClass->ParentName + ", but its function is marked as final.");
			}

			// We found the parent function, so we break from the loop.
			break;
		}
	}
}


