// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_PlusEqual.h"

UAST_PlusEqual::UAST_PlusEqual()
{
	Description = "+=";
	Sign = "+=";
	Precedence = 16;
	Associativity = EOperatorAssociativity::RightToLeft;
}


