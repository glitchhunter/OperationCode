// Fill out your copyright notice in the Description page of Project Settings.

#include "SL_ForbidAction.h"

void USL_ForbidAction::StartAnalysis(UAST_Node* RootNode)
{
	if (!ActionToForbid) return;

	RecursiveCheck(RootNode);
}

bool USL_ForbidAction::RecursiveCheck(UAST_Node* node)
{
	if (node->GetClass()->IsChildOf(ActionToForbid))
	{
		ThrowError(ErrorMessage);
		return true;
	}

	for (UAST_Node* currentChild : node->GetChildren())
	{
		if (RecursiveCheck(currentChild)) return true;
	}

	return false;
}


