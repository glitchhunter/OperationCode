// Fill out your copyright notice in the Description page of Project Settings.

#include "BoolClass.h"

#include "Interpreter/Predefined/Bool/Logical/Bool_And_BoolBool.h"
#include "Interpreter/Predefined/Bool/Logical/Bool_Equals_BoolBool.h"
#include "Interpreter/Predefined/Bool/Logical/Bool_Not_Bool.h"
#include "Interpreter/Predefined/Bool/Logical/Bool_NotEqual_BoolBool.h"
#include "Interpreter/Predefined/Bool/Logical/Bool_Or_BoolBool.h"

#include "Interpreter/Predefined/Bool/Conversions/Float_ConvertAuto_Bool.h"
#include "Interpreter/Predefined/Bool/Conversions/Int_ConvertAuto_Bool.h"
#include "Interpreter/Predefined/Bool/Conversions/String_ConvertAuto_Bool.h"

#include "Interpreter/Predefined/Bool/Bool_Equal_BoolBool.h"

UBoolClass::UBoolClass()
{
	Name = "bool";
	ParentName = "class";

	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_And_BoolBool>(TEXT("And")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_Or_BoolBool>(TEXT("Or")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_Not_Bool>(TEXT("Not")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_NotEqual_BoolBool>(TEXT("Not equal")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_Equal_BoolBool>(TEXT("Equal")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_Equals_BoolBool>(TEXT("Equals")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UFloat_ConvertAuto_Bool>(TEXT("Convert to float")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UInt_ConvertAuto_Bool>(TEXT("Convert to int")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UString_ConvertAuto_Bool>(TEXT("Convert to string")));
}



