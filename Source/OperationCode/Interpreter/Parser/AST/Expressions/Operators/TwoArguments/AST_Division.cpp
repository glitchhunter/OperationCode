// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_Division.h"

UAST_Division::UAST_Division()
{
	Description = "/";
	Sign = "/";
	Precedence = 5;
	Associativity = EOperatorAssociativity::LeftToRight;
}


