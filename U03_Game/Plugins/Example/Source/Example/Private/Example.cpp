#include "Example.h"
#include "GameplayDebugger.h"
#include "01_DebugCategory/CGameplayDebugCategory.h"

#define LOCTEXT_NAMESPACE "FExampleModule"

void FExampleModule::StartupModule()
{
	UE_LOG(LogTemp, Error, L"START MODULE");

	//DebugCategory
	{
		IGameplayDebugger& gameplayDebugger = IGameplayDebugger::Get();

		IGameplayDebugger::FOnGetCategory category = IGameplayDebugger::FOnGetCategory::CreateStatic(&CGameplayDebugCategory::MakeInstance);

		//TODO. 아래 코드 설명해야 함
		gameplayDebugger.RegisterCategory("ExampleCategory", category, EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 5);
		gameplayDebugger.NotifyCategoriesChanged();
		
		
	}
}

void FExampleModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, L"SHUTDOWN MODULE");
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FExampleModule, Example)