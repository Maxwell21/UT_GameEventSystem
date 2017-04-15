#pragma once

#include "ModuleManager.h"

// AssetTools
#include "IAssetTools.h"
#include "IAssetTypeActions.h"

class FCT_GameEventSystemEditorModule : public IModuleInterface
{

private:

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

	/** All created asset type actions.  Cached here so that we can unregister them during shutdown. */
	TArray< TSharedPtr<IAssetTypeActions> > CreatedAssetTypeActions;
	
	EAssetTypeCategories::Type GameEventAssetCategoryBit;

public:
	
	/************************************************************************/
	/* METHODS                                                              */
	/************************************************************************/

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	void RegisterAssetTypeAction(IAssetTools& AssetTools, TSharedRef<IAssetTypeActions> Action);
};