// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class OperationCodeTarget : TargetRules
{
	public OperationCodeTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "OperationCode" } );

        bUseUnityBuild = false;
	}
}
