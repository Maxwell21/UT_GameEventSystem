// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CT_GameEventSystemEditor : ModuleRules
{
	public CT_GameEventSystemEditor(TargetInfo Target)
	{
		
		PublicIncludePaths.AddRange(
			new string[] {
				"CT_GameEventSystemEditor/Public"
				// ... add public include paths required here ...
			}
			);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
				"CT_GameEventSystemEditor/Private",
				// ... add other private include paths required here ...
			}
			);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
				// ... add other public dependencies that you statically link with here ...
			}
			);


        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "EditorStyle",
                "UnrealEd",
                "AssetTools",
                "Projects",
                "LevelEditor",
                "InputCore",
                "WorkspaceMenuStructure",
                "CT_GameEventSystem",
				// ... add private dependencies that you statically link with here ...	
			}
			);
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
				// ... add any modules that your module loads dynamically here ...
			}
			);
	}
}
