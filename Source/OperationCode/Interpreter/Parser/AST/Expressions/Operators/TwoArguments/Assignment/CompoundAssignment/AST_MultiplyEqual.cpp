// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_MultiplyEqual.h"

UAST_MultiplyEqual::UAST_MultiplyEqual()
{
	Description = "*=";
	Sign = "*=";
	Precedence = 16;
	Associativity = EOperatorAssociativity::RightToLeft;
}


