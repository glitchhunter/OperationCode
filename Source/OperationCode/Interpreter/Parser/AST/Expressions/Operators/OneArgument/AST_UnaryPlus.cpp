// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_UnaryPlus.h"

UAST_UnaryPlus::UAST_UnaryPlus()
{
	Description = "Unary +";
	Sign = "+";
	Precedence = 3;
	Associativity = EOperatorAssociativity::RightToLeft;
}


