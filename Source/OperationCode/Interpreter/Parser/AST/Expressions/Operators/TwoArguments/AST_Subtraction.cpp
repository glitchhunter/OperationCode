// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_Subtraction.h"

UAST_Subtraction::UAST_Subtraction()
{
	Description = "-";
	Sign = "-";
	Precedence = 6;
	Associativity = EOperatorAssociativity::LeftToRight;
}


