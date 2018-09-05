// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_Node.h"

UAST_Node::UAST_Node()
{
	Description = "AST node";
}

UWorld* UAST_Node::GetWorld() const
{
	if (!HasAnyFlags(RF_ClassDefaultObject))
	{
		return GetOuter()->GetWorld();
	}
	else
	{
		return nullptr;
	}
}

TArray<UAST_Node*> UAST_Node::GetChildren() const
{
	return TArray<UAST_Node*>();
}

FString UAST_Node::GetDescription() const
{
	return Description;
}


