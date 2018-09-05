// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_IncrementSufix.h"

UAST_IncrementSufix::UAST_IncrementSufix()
{
	Description = "++ (suffix)";
	Sign = "++ (suffix)";
	Precedence = 2;
	Associativity = EOperatorAssociativity::LeftToRight;
}


