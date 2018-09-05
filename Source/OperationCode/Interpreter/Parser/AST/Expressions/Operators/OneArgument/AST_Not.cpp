// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_Not.h"

UAST_Not::UAST_Not()
{
	Description = "!";
	Sign = "!";
	Precedence = 3;
	Associativity = EOperatorAssociativity::RightToLeft;
}


