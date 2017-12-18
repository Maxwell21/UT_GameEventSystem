/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#pragma once

#include "ModuleManager.h"
#include "MultiBoxBuilder.h"

// AssetTools
#include "IAssetTools.h"
#include "IAssetTypeActions.h"

class FUT_GameEventSystemEditorModule : public IModuleInterface
{

private:

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

	/** All created asset type actions.  Cached here so that we can unregister them during shutdown. */
	TArray< TSharedPtr<IAssetTypeActions> > CreatedAssetTypeActions;
	
	EAssetTypeCategories::Type AssetCategoryBit;

public:
	
	/************************************************************************/
	/* METHODS                                                              */
	/************************************************************************/

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);
	virtual EAssetTypeCategories::Type GetAssetCategoryBit() const;
	
	static inline FUT_GameEventSystemEditorModule& Get()
	{
		return FModuleManager::LoadModuleChecked<FUT_GameEventSystemEditorModule>("UT_GameEventSystemEditor");
	};
};