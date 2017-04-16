#include "CT_GameEventSystemEditor.h"
#include "GameEventDebuggerCommands.h"
#include "Engine.h"

#define LOCTEXT_NAMESPACE "GameEventDebuggerCommands"

void FGameEventDebuggerCommands::RegisterCommands()
{
	UI_COMMAND(ShowGameEventDebugger, "Game Event Debugger", "List all events of the GameEventManager selected.", EUserInterfaceActionType::Button, FInputChord());
}

void FGameEventDebuggerCommands::OnShowGameEventDebugger()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Red, TEXT("Game Event Debugger OPENED"));
	TSharedRef<class FGlobalTabmanager> TabManager = FGlobalTabmanager::Get();
	TabManager->InvokeTab(FGameEventDebuggerTab::GameEventDebbugerTabName);
}

#undef LOCTEXT_NAMESPACE
