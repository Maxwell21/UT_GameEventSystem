/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#include "UT_GameEventSystemEditor.h"
#include "AssetToolsModule.h"
#include "AssetTypeActions_GameEvent.h"
#include "AssetTypeActions_GameEventContainer.h"
#include "AssetTypeActions_GameEventManager.h"
#include "GameplayDebugger.h"
#include "GameplayDebuggerCategory_GEvent.h"

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

	#if WITH_GAMEPLAY_DEBUGGER
		//If the gameplay debugger is available, register the category and notify the editor about the changes
		IGameplayDebugger& GameplayDebuggerModule = IGameplayDebugger::Get();
		GameplayDebuggerModule.RegisterCategory("UmbraGameEvent", IGameplayDebugger::FOnGetCategory::CreateStatic(&FGameplayDebuggerCategory_GEvent::MakeInstance), EGameplayDebuggerCategoryState::EnabledInGameAndSimulate);
		GameplayDebuggerModule.NotifyCategoriesChanged();
	#endif

}

void FUT_GameEventSystemEditorModule::ShutdownModule()
{
	#if WITH_GAMEPLAY_DEBUGGER
		if (IGameplayDebugger::IsAvailable())
		{
			IGameplayDebugger& GameplayDebuggerModule = IGameplayDebugger::Get();
			GameplayDebuggerModule.UnregisterCategory("UmbraGameEvent");
		}
	#endif
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