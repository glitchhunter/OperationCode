// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_DecrementPrefix.h"

UAST_DecrementPrefix::UAST_DecrementPrefix()
{
	Description = "-- (prefix)";
	Sign = "-- (prefix)";
	Precedence = 3;
	Associativity = EOperatorAssociativity::RightToLeft;
}


