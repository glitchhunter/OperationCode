// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_Greater.h"

UAST_Greater::UAST_Greater()
{
	Description = ">";
	Sign = ">";
	Precedence = 9;
	Associativity = EOperatorAssociativity::LeftToRight;
}


