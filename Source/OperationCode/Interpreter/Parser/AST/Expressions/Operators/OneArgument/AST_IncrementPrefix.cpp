// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_IncrementPrefix.h"

UAST_IncrementPrefix::UAST_IncrementPrefix()
{
	Description = "++ (prefix)";
	Sign = "++ (prefix)";
	Precedence = 3;
	Associativity = EOperatorAssociativity::RightToLeft;
}


