#include "CT_GameEventSystemEditor.h"
#include "AssetTypeActions_GameEventBehavior.h"
#include "BlueprintEditorModule.h"
#include "GameEventBehavior.h"

FText FAssetTypeActions_GameEventBehavior::GetName() const
{
	return NSLOCTEXT("AssetTypeActions", "AssetTypeActions_GameEventBehavior", "Game Event Behavior");
}

FColor FAssetTypeActions_GameEventBehavior::GetTypeColor() const
{
	return FColor::Red;
}

UClass* FAssetTypeActions_GameEventBehavior::GetSupportedClass() const
{
	return UGameEventBehavior::StaticClass();
}

uint32 FAssetTypeActions_GameEventBehavior::GetCategories()
{
	return EAssetTypeCategories::Gameplay;
}

bool FAssetTypeActions_GameEventBehavior::CanLocalize() const
{
	return false;
}

FText FAssetTypeActions_GameEventBehavior::GetAssetDescription(const FAssetData& AssetData) const
{
	return FText::FromString(FString(TEXT("Game Event Behavior.")));
}