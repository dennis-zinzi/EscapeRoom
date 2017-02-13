// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class EscapeRoomGame : ModuleRules
{
	private static readonly string[] ranges = new string[] { "Core", "CoreUObject", "Engine", "InputCore" };
	private static readonly string[] emptyRange = new string[] {  };

	public EscapeRoomGame(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(ranges);

		PrivateDependencyModuleNames.AddRange(emptyRange);

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
