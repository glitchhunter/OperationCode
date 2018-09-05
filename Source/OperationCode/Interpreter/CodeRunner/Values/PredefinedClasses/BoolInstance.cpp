// Fill out your copyright notice in the Description page of Project Settings.

#include "BoolInstance.h"
#include "Interpreter/CodeRunner/RuntimeStates/Implicit/RTS_InstanceCreator.h"

UBoolInstance* UBoolInstance::Duplicate_Implementation()
{
	return URTS_InstanceCreator::CreateBoolValue(CodeRunner, Value);
}