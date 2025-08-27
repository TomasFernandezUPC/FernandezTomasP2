// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FernandezTomasP2 : ModuleRules
{
	public FernandezTomasP2(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"FernandezTomasP2",
			"FernandezTomasP2/Variant_Platforming",
			"FernandezTomasP2/Variant_Platforming/Animation",
			"FernandezTomasP2/Variant_Combat",
			"FernandezTomasP2/Variant_Combat/AI",
			"FernandezTomasP2/Variant_Combat/Animation",
			"FernandezTomasP2/Variant_Combat/Gameplay",
			"FernandezTomasP2/Variant_Combat/Interfaces",
			"FernandezTomasP2/Variant_Combat/UI",
			"FernandezTomasP2/Variant_SideScrolling",
			"FernandezTomasP2/Variant_SideScrolling/AI",
			"FernandezTomasP2/Variant_SideScrolling/Gameplay",
			"FernandezTomasP2/Variant_SideScrolling/Interfaces",
			"FernandezTomasP2/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
