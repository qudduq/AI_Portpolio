using UnrealBuildTool;

public class AI_Portpolio : ModuleRules
{
	public AI_Portpolio(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.Add(ModuleDirectory);

		PublicDependencyModuleNames.AddRange(new string[] 
		{
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore",
			"Landscape",
			"UMG",
			"Slate",
			"SlateCore",
			"AIModule",
			"GameplayTasks",
		});

		PrivateDependencyModuleNames.AddRange(new string[] 
		{
			
		});
	}
}
