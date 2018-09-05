// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_EqualTo.h"

UAST_EqualTo::UAST_EqualTo()
{
	Description = "==";
	Sign = "==";
	Precedence = 10;
	Associativity = EOperatorAssociativity::LeftToRight;
}


