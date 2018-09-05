// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_MinusEqual.h"

UAST_MinusEqual::UAST_MinusEqual()
{
	Description = "-=";
	Sign = "-=";
	Precedence = 16;
	Associativity = EOperatorAssociativity::RightToLeft;
}


