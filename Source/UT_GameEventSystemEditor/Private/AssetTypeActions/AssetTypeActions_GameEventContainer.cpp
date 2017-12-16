/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#include "AssetTypeActions_GameEventContainer.h"
#include "UT_GameEventSystemEditor.h"
#include "BlueprintEditorModule.h"
#include "GameEventContainer.h"

FText FAssetTypeActions_GameEventContainer::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_GameEventContainer", "Game Event Container");
}

FColor FAssetTypeActions_GameEventContainer::GetTypeColor() const
{
	return FColor(255, 200, 200);
}

UClass* FAssetTypeActions_GameEventContainer::GetSupportedClass() const
{
	return UGameEventContainer::StaticClass();
}

uint32 FAssetTypeActions_GameEventContainer::GetCategories()
{
	FUT_GameEventSystemEditorModule& GameEventSystemEditorModule = FModuleManager::GetModuleChecked<FUT_GameEventSystemEditorModule>("UT_GameEventSystemEditor").Get();
	return GameEventSystemEditorModule.GetAssetCategoryBit();
}

bool FAssetTypeActions_GameEventContainer::CanLocalize() const
{
	return false;
}

FText FAssetTypeActions_GameEventContainer::GetAssetDescription(const FAssetData& AssetData) const
{
	return FText::FromString(FString(TEXT("Game Event Container")));
}