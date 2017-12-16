/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#include "UT_GameEventSystemEditor.h"
#include "AssetToolsModule.h"
#include "AssetTypeActions_GameEvent.h"
#include "AssetTypeActions_GameEventContainer.h"
#include "AssetTypeActions_GameEventManager.h"

#define LOCTEXT_NAMESPACE "FUT_GameEventSystemEditorModule"

void FUT_GameEventSystemEditorModule::StartupModule()
{
	// Register asset types
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();
	AssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("UT_Umbra")), LOCTEXT("UmbraAssetCategory", "Umbra"));
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_GameEvent));
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_GameEventContainer));
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_GameEventManager));
	// End register asset types
}

void FUT_GameEventSystemEditorModule::ShutdownModule()
{

}

void FUT_GameEventSystemEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

EAssetTypeCategories::Type FUT_GameEventSystemEditorModule::GetAssetCategoryBit() const
{
	return this->AssetCategoryBit;
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FUT_GameEventSystemEditorModule, UT_GameEventSystemEditor)