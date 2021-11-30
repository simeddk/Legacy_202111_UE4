#include "Example.h"
#include "GameplayDebugger.h"
#include "LevelEditor.h"
#include "Styling/SlateStyleRegistry.h"
#include "Interfaces/IPluginManager.h"
#include "AssetToolsModule.h"
#include "PropertyEditorModule.h"
#include "01_DebugCategory/CGameplayDebugCategory.h"
#include "02_ToolbarCommand/CToolbarCommand.h"
#include "03_CutomDataAsset/CDataAssetToolAction.h"
#include "04_EditorDetailPanel/CEditorDetailPanel.h"
#include "Objects/CButtonActor.h"

#define LOCTEXT_NAMESPACE "FExampleModule"

void FExampleModule::StartupModule()
{
	//TArray<const FSlateBrush*> brushes;
	//FEditorStyle::GetResources(brushes);
	//for (const FSlateBrush* brush : brushes)
	//	GLog->Log(brush->GetResourceName().ToString());

	UE_LOG(LogTemp, Error, L"START MODULE");

	//StyleSet
	{
		//스타일셋 생성
		StyleSet = MakeShareable(new FSlateStyleSet("ExmapleStyle"));

		//컨텐츠 디렉토리 루트 잡아주기
		FString path = IPluginManager::Get().FindPlugin("Example")->GetContentDir();
		StyleSet->SetContentRoot(path);

		//아이콘 얻어서 세팅해주기
		FSlateImageBrush* brush = new FSlateImageBrush(path / L"Icon.png", FVector2D(48, 48));
		StyleSet->Set("Example.ToolbarIcon", brush);

		//실제 등록
		FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
	}

	//DebugCategory
	{
		//게임플레이 디버거 싱글톤 얻어오기
		IGameplayDebugger& gameplayDebugger = IGameplayDebugger::Get();

		//커스텀 카테고리 객체 생성하기
		IGameplayDebugger::FOnGetCategory category = IGameplayDebugger::FOnGetCategory::CreateStatic(&CGameplayDebugCategory::MakeInstance);

		//커스텀 카테고리 등록하기
		gameplayDebugger.RegisterCategory("ExampleCategory", category, EGameplayDebuggerCategoryState::EnabledInGameAndSimulate, 5);
		gameplayDebugger.NotifyCategoriesChanged();
	}

	//ToolbarButton
	{
		//툴바 확장 등록
		CToolbarCommand::Register();
		ToolbarExtender = MakeShareable(new FExtender());
		
		//실제 툴바에 버튼 추가
		TSharedPtr<FUICommandList> commandList = MakeShareable(new FUICommandList());
		commandList->MapAction
		(
			CToolbarCommand::Get().Button,
			FExecuteAction::CreateRaw(this, &FExampleModule::ToolbarButton_Clicked),
			FCanExecuteAction()
		);

		Extension = ToolbarExtender->AddToolBarExtension
		(
			"Compile",
			EExtensionHook::After,
			commandList,
			FToolBarExtensionDelegate::CreateRaw(this, &FExampleModule::AddToolbarExtension)
		);

		//레벨 에디터에 붙여주기
		FLevelEditorModule& levelEditor = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
		levelEditor.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);

	
	}

	//AssetTool
	{
		//에셋툴 모듈 매니저 가져오기
		IAssetTools& assetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

		//카테고리 설정
		//EAssetTypeCategories::Type category = EAssetTypeCategories::Misc; //기타
		EAssetTypeCategories::Type category = assetTools.RegisterAdvancedAssetCategory(FName(), FText::FromString("Awesome Category")); //커스텀

		//에셋툴 액션 생성
		Action = MakeShareable(new CDataAssetToolAction(category));

		//에셋툴에 액션 등록
		assetTools.RegisterAssetTypeActions(Action.ToSharedRef());
	}

	
	//Detail Panel
	{
		//디테일패널(PropertyEditor 얻어오기)
		FPropertyEditorModule& editor = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor");

		//특정 액터(CButtonActor)에 우리가 만든 CEditorDetailPanel 패널 붙이기(버튼 들어있음)
		editor.RegisterCustomClassLayout
		(
			ACButtonActor::StaticClass()->GetFName(),
			FOnGetDetailCustomizationInstance::CreateStatic(&CEditorDetailPanel::MakeInstance)
		);
	}
}

void FExampleModule::ShutdownModule()
{
	UE_LOG(LogTemp, Error, L"SHUTDOWN MODULE");

	if (IGameplayDebugger::IsAvailable())
	{
		IGameplayDebugger& gameplayDebugger = IGameplayDebugger::Get();
		gameplayDebugger.UnregisterCategory("ExampleCategory");
	}

	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
	StyleSet.Reset();

	ToolbarExtender->RemoveExtension(Extension.ToSharedRef());
	ToolbarExtender.Reset();

}

void FExampleModule::AddToolbarExtension(class FToolBarBuilder& InBuilder)
{
	FSlateIcon icon = FSlateIcon("ExmapleStyle", "Example.ToolbarIcon");

	InBuilder.AddToolBarButton
	(
		CToolbarCommand::Get().Button,
		NAME_None,
		FText::FromString("YesJam"),
		FText::FromString("NoJam"),
		icon
	);
}

void FExampleModule::ToolbarButton_Clicked()
{
	UE_LOG(LogTemp, Error, L"Hello Hell World~~~");
}


#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FExampleModule, Example)