// Fill out your copyright notice in the Description page of Project Settings.

#include "FloatClass.h"

#include "Interpreter/Predefined/Float/Arithmetic/Float_Add_FloatFloat.h"
#include "Interpreter/Predefined/Float/Arithmetic/Float_Divide_FloatFloat.h"
#include "Interpreter/Predefined/Float/Arithmetic/Float_Multiply_FloatFloat.h"
#include "Interpreter/Predefined/Float/Arithmetic/Float_Subtract_FloatFloat.h"

#include "Interpreter/Predefined/Float/Logical/Bool_Equals_FloatFloat.h"
#include "Interpreter/Predefined/Float/Logical/Bool_Greater_FloatFloat.h"
#include "Interpreter/Predefined/Float/Logical/Bool_GreaterOrEqual_FloatFloat.h"
#include "Interpreter/Predefined/Float/Logical/Bool_Less_FloatFloat.h"
#include "Interpreter/Predefined/Float/Logical/Bool_LessOrEqual_FloatFloat.h"
#include "Interpreter/Predefined/Float/Logical/Bool_NotEqual_FloatFloat.h"

#include "Interpreter/Predefined/Float/Conversions/String_ConvertAuto_Float.h"
#include "Interpreter/Predefined/Float/Float_Equal_FloatFloat.h"

UFloatClass::UFloatClass()
{
	Name = "float";
	ParentName = "class";

	FunctionDefinitions.Add(CreateDefaultSubobject<UFloat_Add_FloatFloat>(TEXT("Add")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UFloat_Divide_FloatFloat>(TEXT("Divide")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UFloat_Multiply_FloatFloat>(TEXT("Multiply")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UFloat_Subtract_FloatFloat>(TEXT("Subtract")));

	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_Equals_FloatFloat>(TEXT("Equals")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_GreaterOrEqual_FloatFloat>(TEXT("Greater or equal")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_Greater_FloatFloat>(TEXT("Greater")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_LessOrEqual_FloatFloat>(TEXT("Less or equal")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_Less_FloatFloat>(TEXT("Less")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_NotEqual_FloatFloat>(TEXT("Not equal")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UString_ConvertAuto_Float>(TEXT("Convert to string")));

	FunctionDefinitions.Add(CreateDefaultSubobject<UFloat_Equal_FloatFloat>(TEXT("Equal")));
}


