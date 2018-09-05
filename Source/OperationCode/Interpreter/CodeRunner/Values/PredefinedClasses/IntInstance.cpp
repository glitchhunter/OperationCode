// Fill out your copyright notice in the Description page of Project Settings.

#include "IntInstance.h"
#include "Interpreter/CodeRunner/RuntimeStates/Implicit/RTS_InstanceCreator.h"

UIntInstance* UIntInstance::Duplicate_Implementation()
{
	return URTS_InstanceCreator::CreateIntValue(CodeRunner, Value);
}
