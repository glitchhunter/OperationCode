// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/Implicit/ImplicitRTS.h"
#include "RTS_StaticInitializer.generated.h"

class UAST_ClassDefinition;
class UAST_VariableDefinition;

/**
 * 
 */
UCLASS()
class URTS_StaticInitializer : public UImplicitRTS
{
	GENERATED_BODY()
	
public:

	virtual void RunStep() override;



protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UAST_ClassDefinition*> AllClasses;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool ClassesCached;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 ClassIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	int32 VariableIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool ExpectingValueReturn;
	
	
};
