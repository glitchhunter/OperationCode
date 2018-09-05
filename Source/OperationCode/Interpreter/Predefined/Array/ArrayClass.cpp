// Fill out your copyright notice in the Description page of Project Settings.

#include "ArrayClass.h"
#include "Interpreter/Predefined/Array/Array_OperatorEqual_ArrayArray.h"
#include "Interpreter/Predefined/Array/Int_Add_Element.h"
#include "Interpreter/Predefined/Array/Int_Size.h"
#include "Interpreter/Predefined/Array/Void_Insert_Element.h"
#include "Interpreter/Predefined/Array/Void_Remove_Int.h"
#include "Interpreter/Predefined/Array/Element_Get_Int.h"

UArrayClass::UArrayClass()
{
	Name = "array";
	ParentName = "class";

	FunctionDefinitions.Add(CreateDefaultSubobject<UArray_OperatorEqual_ArrayArray>("Equal"));
	FunctionDefinitions.Add(CreateDefaultSubobject<UInt_Add_Element>("Add"));
	FunctionDefinitions.Add(CreateDefaultSubobject<UInt_Size>("Size"));
	FunctionDefinitions.Add(CreateDefaultSubobject<UVoid_Insert_Element>("Insert"));
	FunctionDefinitions.Add(CreateDefaultSubobject<UVoid_Remove_Int>("Remove"));
	FunctionDefinitions.Add(CreateDefaultSubobject<UElement_Get_Int>("Get"));
}




