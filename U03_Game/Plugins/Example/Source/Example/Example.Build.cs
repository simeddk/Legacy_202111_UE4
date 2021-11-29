using UnrealBuildTool;

public class Example : ModuleRules
{
	public Example(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;


		PublicIncludePaths.Add(ModuleDirectory);

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
			}
			);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"CoreUObject",
				"Engine",
				"Slate",
				"SlateCore",
				"GameplayDebugger",
				"EditorStyle",
				"LevelEditor",
				"Projects",
				"UnrealEd",
				"AssetTools",
				"PropertyEditor",
				"U03_Game"
			}
			);


		if (Target.bBuildDeveloperTools || Target.Configuration != UnrealTargetConfiguration.Shipping)
			PrivateDependencyModuleNames.Add("GameplayDebugger");
	}
}
