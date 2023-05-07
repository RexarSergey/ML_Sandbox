// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class PDP_Tasks : ModuleRules
{
	public PDP_Tasks(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "EnhancedInput" });
	}
}
