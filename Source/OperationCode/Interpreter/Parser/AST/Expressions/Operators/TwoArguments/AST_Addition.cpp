// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_Addition.h"

UAST_Addition::UAST_Addition()
{
	Description = "+";
	Sign = "+";
	Precedence = 6;
	Associativity = EOperatorAssociativity::LeftToRight;
}


