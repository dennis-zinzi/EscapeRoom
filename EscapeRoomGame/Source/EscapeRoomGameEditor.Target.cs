// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class EscapeRoomGameEditorTarget : TargetRules
{
	public EscapeRoomGameEditorTarget(TargetInfo Target)
	{
		Type = TargetType.Editor;

        //Enable IWYU for v4.17+
        bUseUnityBuild = false;
        bUsePCHFiles = false;
    }

    //
    // TargetRules interface.
    //

    public override void SetupBinaries(
		TargetInfo Target,
		ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
		ref List<string> OutExtraModuleNames
		)
	{
		OutExtraModuleNames.AddRange( new string[] { "EscapeRoomGame" } );
	}
}
