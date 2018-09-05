// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_Less.h"

UAST_Less::UAST_Less()
{
	Description = "<";
	Sign = "<";
	Precedence = 9;
	Associativity = EOperatorAssociativity::LeftToRight;
}


