// Fill out your copyright notice in the Description page of Project Settings.

#include "ArrayInstance.h"

UArrayInstance* UArrayInstance::Duplicate_Implementation()
{
	TArray<UValue*> copy;
	for (UValue* val : Value)
	{
		copy.Add(val->Duplicate());
	}

	return URTS_InstanceCreator::CreateArrayValue(CodeRunner, Type, copy);

}



