// Fill out your copyright notice in the Description page of Project Settings.

#include "IntClass.h"

#include "Interpreter/Predefined/Int/Arithmetic/Int_OperatorDivide_IntInt.h"
#include "Interpreter/Predefined/Int/Arithmetic/Int_OperatorMinus_IntInt.h"
#include "Interpreter/Predefined/Int/Arithmetic/Int_OperatorMinusMinusPrefix_Int.h"
#include "Interpreter/Predefined/Int/Arithmetic/Int_OperatorMinusMinusSuffix_int.h"
#include "Interpreter/Predefined/Int/Arithmetic/Int_OperatorModulo_IntInt.h"
#include "Interpreter/Predefined/Int/Arithmetic/Int_OperatorMultiply_IntInt.h"
#include "Interpreter/Predefined/Int/Arithmetic/Int_OperatorPlus_IntInt.h"
#include "Interpreter/Predefined/Int/Arithmetic/Int_OperatorPlusPlusPrefix_Int.h"
#include "Interpreter/Predefined/Int/Arithmetic/Int_OperatorPlusPlusSuffix_Int.h"

#include "Interpreter/Predefined/Int/Logical/Bool_Equals_IntInt.h"
#include "Interpreter/Predefined/Int/Logical/Bool_Greater_IntInt.h"
#include "Interpreter/Predefined/Int/Logical/Bool_GreaterOrEqual_IntInt.h"
#include "Interpreter/Predefined/Int/Logical/Bool_Less_IntInt.h"
#include "Interpreter/Predefined/Int/Logical/Bool_LessOrEqual_IntInt.h"
#include "Interpreter/Predefined/Int/Logical/Bool_NotEqual_IntInt.h"

#include "Interpreter/Predefined/Int/Conversions/Bool_ConvertAuto_Int.h"
#include "Interpreter/Predefined/Int/Conversions/Float_ConvertAuto_Int.h"
#include "Interpreter/Predefined/Int/Conversions/String_ConvertAuto_Int.h"

#include "Interpreter/Predefined/Int/Int_OperatorEqual_IntInt.h"

UIntClass::UIntClass()
{
	Name = "int";
	ParentName = "class";

	FunctionDefinitions.Add(CreateDefaultSubobject<UInt_OperatorDivide_IntInt>(TEXT("Divide")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UInt_OperatorMinus_IntInt>(TEXT("Subtract")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UInt_OperatorMinusMinusPrefix_Int>(TEXT("--(prefix)")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UInt_OperatorMinusMinusSuffix_int>(TEXT("--(suffix)")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UInt_OperatorModulo_IntInt>(TEXT("Modulo")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UInt_OperatorMultiply_IntInt>(TEXT("Multiply")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UInt_OperatorPlus_IntInt>(TEXT("Add")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UInt_OperatorPlusPlusPrefix_Int>(TEXT("++(prefix)")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UInt_OperatorPlusPlusSuffix_Int>(TEXT("++(suffix)")));

	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_Equals_IntInt>(TEXT("Equals")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_Greater_IntInt>(TEXT("Greater")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_GreaterOrEqual_IntInt>(TEXT("Greater or equal")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_Less_IntInt>(TEXT("Less")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_LessOrEqual_IntInt>(TEXT("Less or equal")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_NotEqual_IntInt>(TEXT("Not equal")));

	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_ConvertAuto_Int>(TEXT("Convert to bool")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UFloat_ConvertAuto_Int>(TEXT("Convert to float")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UString_ConvertAuto_Int>(TEXT("Convert to string")));

	FunctionDefinitions.Add(CreateDefaultSubobject<UInt_OperatorEqual_IntInt>(TEXT("Assignment")));
}


