// Fill out your copyright notice in the Description page of Project Settings.

#include "StringClass.h"

#include "Interpreter/Predefined/String/Bool_Equals_StringString.h"
#include "Interpreter/Predefined/String/Bool_EqualsNoCase_StringString.h"
#include "Interpreter/Predefined/String/Bool_NotEqual_StringString.h"
#include "Interpreter/Predefined/String/Bool_NotEqualNoCase_StringString.h"
#include "Interpreter/Predefined/String/String_Concatenate_StringString.h"
#include "Interpreter/Predefined/String/String_Equal_StringString.h"

UStringClass::UStringClass()
{
	Name = "string";
	ParentName = "class";

	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_Equals_StringString>(TEXT("Equals")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_EqualsNoCase_StringString>(TEXT("Equals ignore case")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_NotEqual_StringString>(TEXT("Not equal")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_NotEqualNoCase_StringString>(TEXT("Not equal ignore case")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UString_Concatenate_StringString>(TEXT("Concatenate")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UString_Equal_StringString>(TEXT("Equal")));
}


