#include "CT_GameEventSystemEditor.h"

#include "GameEventDebuggerCommands.h"
#include "GameEventDebuggerTab.h"
#include "AssetTypeActions_GameEvent.h"
#include "AssetTypeActions_GameEventContainer.h"
#include "AssetTypeActions_GameEventBehavior.h"
#include "AssetTypeActions_GameEventManager.h"

#include "AssetToolsModule.h"
#include "LevelEditor.h"
#include "UIAction.h"
#include "WorkspaceMenuStructure.h"
#include "WorkspaceMenuStructureModule.h"

#define LOCTEXT_NAMESPACE "FCT_GameEventSystemEditorModule"

void FCT_GameEventSystemEditorModule::StartupModule()
{
	// Init
	FGameEventEditorStyle::Initialize();
	FGameEventDebuggerTab::Initialize();

	// Register commands
	FGameEventDebuggerCommands::Register();
	CommandList = MakeShareable(new FUICommandList);
	CommandList->MapAction(FGameEventDebuggerCommands::Get().ShowGameEventDebugger,
		FExecuteAction::CreateStatic(&FGameEventDebuggerCommands::OnShowGameEventDebugger)
	);

	// Register asset types
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	GameEventAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("CT_GameEventSystem")), LOCTEXT("GameEventAssetCategory", "GameEvent"));
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_GameEvent));
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_GameEventContainer));
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_GameEventBehavior));
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_GameEventManager));
	// End register asset types

	TSharedRef<class FGlobalTabmanager> TabManager = FGlobalTabmanager::Get();
	TabManager->RegisterNomadTabSpawner(
		FGameEventDebuggerTab::GameEventDebbugerTabName,
		FOnSpawnTab::CreateRaw(FGameEventDebuggerTab::Get().Get(), &FGameEventDebuggerTab::SpawnTab)
	)
		.SetDisplayName(FText::FromName(FGameEventEditorStyle::GetStyleSetName()))
		.SetIcon(FSlateIcon(FGameEventEditorStyle::GetStyleSetName(), "ClassIcon.CT_GameEventSystem"))
		.SetGroup(WorkspaceMenu::GetMenuStructure().GetToolsCategory())
	;
}

void FCT_GameEventSystemEditorModule::ShutdownModule()
{
	FGameEventEditorStyle::Shutdown();
	FGameEventDebuggerCommands::Unregister();

	TSharedRef<class FGlobalTabmanager> TabManager = FGlobalTabmanager::Get();
	TabManager->UnregisterNomadTabSpawner(FGameEventDebuggerTab::GameEventDebbugerTabName);
}

void FCT_GameEventSystemEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCT_GameEventSystemEditorModule, CT_GameEventSystemEditor)