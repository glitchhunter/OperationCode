// Fill out your copyright notice in the Description page of Project Settings.

#include "AST_ModuloEqual.h"

UAST_ModuloEqual::UAST_ModuloEqual()
{
	Description = "%=";
	Sign = "%=";
	Precedence = 16;
	Associativity = EOperatorAssociativity::RightToLeft;
}


