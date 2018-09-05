// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_DivideEqual.h"

UAST_DivideEqual::UAST_DivideEqual()
{
	Description = "/=";
	Sign = "/=";
	Precedence = 16;
	Associativity = EOperatorAssociativity::RightToLeft;
}


