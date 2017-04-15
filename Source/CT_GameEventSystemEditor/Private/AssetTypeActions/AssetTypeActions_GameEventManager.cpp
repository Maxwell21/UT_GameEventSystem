#include "CT_GameEventSystemEditor.h"
#include "AssetTypeActions_GameEventManager.h"
#include "BlueprintEditorModule.h"
#include "GameEventManager.h"

FText FAssetTypeActions_GameEventManager::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_GameEventManager", "Game Event Manager");
}

FColor FAssetTypeActions_GameEventManager::GetTypeColor() const
{
	return FColor::Black;
}

UClass* FAssetTypeActions_GameEventManager::GetSupportedClass() const
{
	return AGameEventManager::StaticClass();
}

uint32 FAssetTypeActions_GameEventManager::GetCategories()
{
	return EAssetTypeCategories::Gameplay;
}

bool FAssetTypeActions_GameEventManager::CanLocalize() const
{
	return false;
}

FText FAssetTypeActions_GameEventManager::GetAssetDescription(const FAssetData& AssetData) const
{
	return FText::FromString(FString(TEXT("Game Event Manager")));
}