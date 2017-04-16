#include "CT_GameEventSystemEditor.h"
#include "GameEventDebuggerTab.h"
#include "SDockTab.h"

const FName FGameEventDebuggerTab::GameEventDebbugerTabName = "GameEventDebuggerTab";

TSharedPtr<class FGameEventDebuggerTab> FGameEventDebuggerTab::GameEventDebbugerTabInstance = nullptr;

void FGameEventDebuggerTab::Initialize()
{
	FGameEventDebuggerTab::GameEventDebbugerTabInstance = MakeShareable(new FGameEventDebuggerTab);
}

TSharedPtr<class FGameEventDebuggerTab> FGameEventDebuggerTab::Get()
{
	return FGameEventDebuggerTab::GameEventDebbugerTabInstance;
}

TSharedRef<SDockTab> FGameEventDebuggerTab::SpawnTab(const FSpawnTabArgs& TabSpawnArgs)
{
	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
	.TabRole(ETabRole::NomadTab)
	[
		SNew(SButton)
		.Text(FText::FromString(TEXT("Work in progress")))
		.HAlign(HAlign_Center)
		.VAlign(VAlign_Center)
	];

	return SpawnedTab;
}
