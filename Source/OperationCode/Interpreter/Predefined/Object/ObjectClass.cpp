// Fill out your copyright notice in the Description page of Project Settings.

#include "ObjectClass.h"

#include "Interpreter/Predefined/Object/Bool_Equals_ObjectObject.h"
#include "Interpreter/Predefined/Object/Object_Equal_ObjectObject.h"

UObjectClass::UObjectClass()
{
	Name = "object";
	ParentName = "";

	FunctionDefinitions.Add(CreateDefaultSubobject<UBool_Equals_ObjectObject>(TEXT("Equals")));
	FunctionDefinitions.Add(CreateDefaultSubobject<UObject_Equal_ObjectObject>(TEXT("Equal")));
}


