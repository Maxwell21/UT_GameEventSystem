// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "CT_GameEventSystemEditor.h"
#include "ModuleManager.h"

// AssetTools
#include "AssetToolsModule.h"
#include "AssetTypeActions_GameEvent.h"

#define LOCTEXT_NAMESPACE "FCT_GameEventSystemEditorModule"

void FCT_GameEventSystemEditorModule::StartupModule()
{
	// Register asset types
	IAssetTools& AssetTools = FModuleManager::LoadModuleChecked<FAssetToolsModule>("AssetTools").Get();

	GameEventAssetCategoryBit = AssetTools.RegisterAdvancedAssetCategory(FName(TEXT("CT_GameEventSystem")), LOCTEXT("GameEventAssetCategory", "GameEvent"));

	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_GameEvent));
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_GameEventContainer));
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_GameEventBehavior));
	RegisterAssetTypeAction(AssetTools, MakeShareable(new FAssetTypeActions_GameEventManager));
}

void FCT_GameEventSystemEditorModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

void FCT_GameEventSystemEditorModule::RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action)
{
	AssetTools.RegisterAssetTypeActions(Action);
	CreatedAssetTypeActions.Add(Action);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCT_GameEventSystemEditorModule, CT_GameEventSystemEditor)