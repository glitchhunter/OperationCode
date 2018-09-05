// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_GreaterOrEqual.h"

UAST_GreaterOrEqual::UAST_GreaterOrEqual()
{
	Description = ">=";
	Sign = ">=";
	Precedence = 9;
	Associativity = EOperatorAssociativity::LeftToRight;
}


