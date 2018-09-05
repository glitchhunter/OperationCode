// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseClass.h"
#include "Interpreter/Predefined/Class/Class_OperatorEqual_ClassClass.h"

UBaseClass::UBaseClass()
{
	Name = "class";
	ParentName = "";

	FunctionDefinitions.Add(CreateDefaultSubobject<UClass_OperatorEqual_ClassClass>(TEXT("Equal")));
}



