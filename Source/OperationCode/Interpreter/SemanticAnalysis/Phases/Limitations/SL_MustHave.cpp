// Fill out your copyright notice in the Description page of Project Settings.

#include "SL_MustHave.h"

void USL_MustHave::StartAnalysis(UAST_Node* RootNode)
{
	if (!MustHaveAction) return;

	UAST_Basic* basic = Cast<UAST_Basic>(RootNode);
	RecursiveCheck(basic->Main);

	if (!found) ThrowError(ErrorMessage);
}

void USL_MustHave::RecursiveCheck(UAST_Node* node)
{
	if (found) return;

	if (node->GetClass()->IsChildOf(MustHaveAction))
	{
		found = true;
		return;
	}

	for (UAST_Node* currentChild : node->GetChildren())
	{
		RecursiveCheck(currentChild);
		if (found) return;
	}
}





