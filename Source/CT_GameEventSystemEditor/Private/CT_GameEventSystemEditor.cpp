#include "CT_GameEventSystemEditor.h"
#include "AssetToolsModule.h"
#include "AssetTypeActions_GameEvent.h"
#include "AssetTypeActions_GameEventContainer.h"
#include "AssetTypeActions_GameEventManager.h"

#define LOCTEXT_NAMESPACE "FCT_GameEventSystemEditorModule"

void FCT_GameEventSystemEditorModule::StartupModule()
{
	// Register asset types
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	GameEventAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("CT_GameEventSystem")), LOCTEXT("GameEventAssetCategory", "GameEvent"));
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_GameEvent));
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_GameEventContainer));
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_GameEventManager));
	// End register asset types
}

void FCT_GameEventSystemEditorModule::ShutdownModule()
{

}

void FCT_GameEventSystemEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCT_GameEventSystemEditorModule, CT_GameEventSystemEditor)