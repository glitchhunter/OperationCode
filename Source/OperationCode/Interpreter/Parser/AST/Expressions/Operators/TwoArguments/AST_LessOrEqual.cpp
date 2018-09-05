// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_LessOrEqual.h"

UAST_LessOrEqual::UAST_LessOrEqual()
{
	Description = "<=";
	Sign = "<=";
	Precedence = 9;
	Associativity = EOperatorAssociativity::LeftToRight;
}


