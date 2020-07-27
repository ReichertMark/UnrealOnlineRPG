// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class MMO : ModuleRules
{
	public MMO(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
    { 
      "Core", 
      "CoreUObject", 
      "Engine", 
      "InputCore", 
      "HeadMountedDisplay",
      "GameplayAbilities",
      "GameplayTags",
      "GameplayTasks",
      "ReplicationGraph",
      "AIModule"
    });

    PrivateDependencyModuleNames.AddRange(new string[]
    {
	  	//"CoreUObject",
	  	//"Engine",
	  	"Slate",
	  	"SlateCore",
      "UMG",
      "Messaging",
      "MessagingCommon",
      "Json",
      "JsonUtilities",
      "Http"
      // ... add private dependencies that you statically link with here ...	
    }
    );
  }
}
