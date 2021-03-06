/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#include "AssetTypeActions_GameEvent.h"
#include "UT_GameEventSystemEditor.h"
#include "BlueprintEditorModule.h"
#include "GameEvent.h"

FText FAssetTypeActions_GameEvent::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_GameEvent", "Game Event");
}

FColor FAssetTypeActions_GameEvent::GetTypeColor() const
{
	return FColor(255, 200, 200);
}

UClass* FAssetTypeActions_GameEvent::GetSupportedClass() const
{
	return UGameEvent::StaticClass();
}

uint32 FAssetTypeActions_GameEvent::GetCategories()
{
	FUT_GameEventSystemEditorModule& GameEventSystemEditorModule = FModuleManager::GetModuleChecked<FUT_GameEventSystemEditorModule>("UT_GameEventSystemEditor").Get();
	return GameEventSystemEditorModule.GetAssetCategoryBit();
}

bool FAssetTypeActions_GameEvent::CanLocalize() const
{
	return false;
}

FText FAssetTypeActions_GameEvent::GetAssetDescription(const FAssetData& AssetData) const
{
	return FText::FromString(FString(TEXT("Game Event")));
}