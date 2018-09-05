// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interpreter/CodeRunner/RuntimeStates/Expressions/Operators/TwoArguments/RTS_TwoArguments.h"
#include "RTS_MemberAccess.generated.h"

UENUM(BlueprintType)
enum class EMemberAccessState : uint8
{
	Initializing,
	RunningCaller,
	RunningCallee
};

class UAST_MemberAccess;

/**
 * 
 */
UCLASS()
class URTS_MemberAccess : public URTS_TwoArguments
{
	GENERATED_BODY()

public:

	virtual void RunStep() override;

	virtual UAST_Node* GetNode() const;

	void SetMemberAccess(UAST_MemberAccess* memberAccess) { MemberAccess = memberAccess; }

protected:

	UPROPERTY()
	UAST_MemberAccess* MemberAccess;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool CalleeHandeled;
	
	
	
	
};
