#include "CT_GameEventSystemEditor.h"

#include "GameEventDebuggerCommands.h"
#include "AssetTypeActions_GameEvent.h"
#include "AssetTypeActions_GameEventContainer.h"
#include "AssetTypeActions_GameEventBehavior.h"
#include "AssetTypeActions_GameEventManager.h"

#include "AssetToolsModule.h"
#include "LevelEditor.h"
#include "UIAction.h"

#define LOCTEXT_NAMESPACE "FCT_GameEventSystemEditorModule"

void FCT_GameEventSystemEditorModule::StartupModule()
{
	// Init
	FGameEventEditorStyle::Initialize();

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
	
	MenuExtender = MakeShareable(new FExtender());
	Extension = MenuExtender->AddMenuExtension("General", EExtensionHook::After, CommandList, FMenuExtensionDelegate::CreateRaw(this, &FCT_GameEventSystemEditorModule::AddMenuExtension));
	
	// Add Menu extender
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor"); 
	LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
}

void FCT_GameEventSystemEditorModule::ShutdownModule()
{
	FGameEventEditorStyle::Shutdown();
	FGameEventDebuggerCommands::Unregister();
}

void FCT_GameEventSystemEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

void FCT_GameEventSystemEditorModule::AddMenuExtension(FMenuBuilder &Builder)
{
	const FGameEventDebuggerCommands& Commands = FGameEventDebuggerCommands::Get();

	Builder.AddMenuEntry(
		Commands.ShowGameEventDebugger,
		NAME_None,
		TAttribute<FText>(),
		TAttribute<FText>(),
		FSlateIcon(FGameEventEditorStyle::GetStyleSetName(), "ClassIcon.CT_GameEventSystem")
	);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCT_GameEventSystemEditorModule, CT_GameEventSystemEditor)