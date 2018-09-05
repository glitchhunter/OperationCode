// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_DirectAssignment.h"

UAST_DirectAssignment::UAST_DirectAssignment()
{
	Description = "=";
	Sign = "=";
	Precedence = 16;
	Associativity = EOperatorAssociativity::RightToLeft;
}


