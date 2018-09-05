// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_UnaryMinus.h"

UAST_UnaryMinus::UAST_UnaryMinus()
{
	Description = "Unary -";
	Sign = "-";
	Precedence = 3;
	Associativity = EOperatorAssociativity::RightToLeft;
}


