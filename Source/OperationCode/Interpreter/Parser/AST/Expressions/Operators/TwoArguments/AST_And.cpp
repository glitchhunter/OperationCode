// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_And.h"

UAST_And::UAST_And()
{
	Description = "&&";
	Sign = "&&";
	Precedence = 14;
	Associativity = EOperatorAssociativity::LeftToRight;
}


