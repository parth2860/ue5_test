// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class ue5_fps_box : ModuleRules
{
	public ue5_fps_box(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "HTTP", "Json", "JsonUtilities" });
	}
}
