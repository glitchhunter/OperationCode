// Fill out your copyright notice in the Description page of Project Settings.

#include "ComplexPredefinedFunction.h"
#include "Interpreter/Predefined/ComplexFunctionDefinitionRTS.h"

URuntimeState* UComplexPredefinedFunction::CreateRuntimeState(UCodeRunner* CodeRunner)
{
	UComplexFunctionDefinitionRTS* RTS_Complex = NewObject<UComplexFunctionDefinitionRTS>(CodeRunner, RTSClass);
	RTS_Complex->Init(CodeRunner);
	//RTS_Complex->SetBasic(this);
	return RTS_Complex;
}


