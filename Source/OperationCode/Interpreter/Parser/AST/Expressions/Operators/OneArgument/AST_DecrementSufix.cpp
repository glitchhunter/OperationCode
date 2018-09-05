// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_DecrementSufix.h"

UAST_DecrementSufix::UAST_DecrementSufix()
{
	Description = "-- (suffix)";
	Sign = "-- (suffix)";
	Precedence = 2;
	Associativity = EOperatorAssociativity::LeftToRight;
}


