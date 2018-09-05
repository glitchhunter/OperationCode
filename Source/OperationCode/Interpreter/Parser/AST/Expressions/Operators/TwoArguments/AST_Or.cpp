// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_Or.h"

UAST_Or::UAST_Or()
{
	Description = "||";
	Sign = "||";
	Precedence = 15;
	Associativity = EOperatorAssociativity::LeftToRight;
}


