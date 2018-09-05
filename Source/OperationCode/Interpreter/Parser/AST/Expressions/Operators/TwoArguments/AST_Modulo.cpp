// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_Modulo.h"

UAST_Modulo::UAST_Modulo()
{
	Description = "%";
	Sign = "%";
	Precedence = 5;
	Associativity = EOperatorAssociativity::LeftToRight;
}


