// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/Predefined/SimplePredefinedFunction.h"
#include "Int_Add_Element.generated.h"

/**
 * 
 */
UCLASS()
class OPERATIONCODE_API UInt_Add_Element : public USimplePredefinedFunction
{
	GENERATED_BODY()

public:

	UInt_Add_Element();

	virtual UValue* Run_Implementation(USimpleFunctionDefinitionRTS* RTS) override;
	
	
	
	
};
