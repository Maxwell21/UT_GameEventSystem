#pragma once

#include "TabManager.h"

/**
 * 
 */
class CT_GAMEEVENTSYSTEMEDITOR_API FGameEventDebuggerTab
{

public:

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

	static const FName GameEventDebbugerTabName;

	static TSharedPtr<class FGameEventDebuggerTab> GameEventDebbugerTabInstance;

	/************************************************************************/
	/* METHODS                                                              */
	/************************************************************************/

	static void Initialize();

	static TSharedPtr<class FGameEventDebuggerTab> Get();

	TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& TabSpawnArgs);

};
