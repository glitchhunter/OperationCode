// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_NotEqualTo.h"

UAST_NotEqualTo::UAST_NotEqualTo()
{
	Description = "!=";
	Sign = "!=";
	Precedence = 10;
	Associativity = EOperatorAssociativity::LeftToRight;
}


