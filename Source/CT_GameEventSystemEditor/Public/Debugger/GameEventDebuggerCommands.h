#pragma once

#include "Framework/Commands/Commands.h"
#include "GameEventEditorStyle.h"

/**
 * 
 */
class CT_GAMEEVENTSYSTEMEDITOR_API FGameEventDebuggerCommands : public TCommands<FGameEventDebuggerCommands>
{

public:

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

	TSharedPtr<FUICommandInfo> ShowGameEventDebugger;

	/************************************************************************/
	/* METHODS                                                              */
	/************************************************************************/

	FGameEventDebuggerCommands() : TCommands<FGameEventDebuggerCommands>(
		TEXT("GameEventDebugger"), // Context name for fast lookup
		NSLOCTEXT("Contexts", "GameEventEditor", "Game Event Debugger"), // Localized context name for displaying
		NAME_None, // Parent
		FGameEventEditorStyle::Get()->GetStyleSetName() // Icon Style Set
		) {};
	
	virtual void RegisterCommands() override;

	static void OnShowGameEventDebugger();
	
};