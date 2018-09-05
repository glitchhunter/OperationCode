// Fill out your copyright notice in the Description page of Project Settings.

#include "StringInstance.h"
#include "Interpreter/CodeRunner/RuntimeStates/Implicit/RTS_InstanceCreator.h"

UStringInstance* UStringInstance::Duplicate_Implementation()
{
	return URTS_InstanceCreator::CreateStringValue(CodeRunner, Value);
}

