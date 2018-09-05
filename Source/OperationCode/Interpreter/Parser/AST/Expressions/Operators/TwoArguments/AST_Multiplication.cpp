// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_Multiplication.h"

UAST_Multiplication::UAST_Multiplication()
{
	Description = "*";
	Sign = "*";
	Precedence = 5;
	Associativity = EOperatorAssociativity::LeftToRight;
}


