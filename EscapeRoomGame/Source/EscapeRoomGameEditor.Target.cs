// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class EscapeRoomGameEditorTarget : TargetRules
{
    public EscapeRoomGameEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

        //Enable IWYU for v4.17+
        bUseUnityBuild = false;
        bUsePCHFiles = false;

        ///Replaces SetupBinaries() as of v4.16
        ExtraModuleNames.Add("EscapeRoomGame");
    }

 //   //
 //   // TargetRules interface.
 //   //

 //   public override void SetupBinaries(
	//	TargetInfo Target,
	//	ref List<UEBuildBinaryConfiguration> OutBuildBinaryConfigurations,
	//	ref List<string> OutExtraModuleNames
	//	)
	//{
	//	OutExtraModuleNames.AddRange( new string[] { "EscapeRoomGame" } );
	//}
}
