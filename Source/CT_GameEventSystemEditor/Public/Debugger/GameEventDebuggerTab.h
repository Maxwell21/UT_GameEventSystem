#pragma once

#include "CoreMinimal.h"
#include "TabManager.h"
#include "GameEventManager.h"
#include "Input/Reply.h"
#include "SListView.h"
#include "SharedPointer.h"

/**
 * 
 */
class CT_GAMEEVENTSYSTEMEDITOR_API FGameEventDebuggerTab : public TSharedFromThis<FGameEventDebuggerTab>
{

public:

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

	static const FName GameEventDebbugerTabName;

	static TSharedPtr<class FGameEventDebuggerTab> GameEventDebbugerTabInstance;

	/** The list view widget for our GameEvent list */
	TSharedPtr<SListView<TSharedRef<class UGameEventObject>>> GameEventListView;

	/** List of everything that we want to display */
	TArray<TSharedRef<class UGameEventObject>> GameEventListItems;

	/************************************************************************/
	/* METHODS                                                              */
	/************************************************************************/

	static void Initialize();

	static TSharedPtr<class FGameEventDebuggerTab> Get();

	TSharedRef<SDockTab> SpawnTab(const FSpawnTabArgs& TabSpawnArgs);

	AGameEventManager* GetSelectedManager();

	FReply OnRefreshList();

	void DisplayList();

	TSharedRef<ITableRow> ListViewOnGenerateRow(TSharedRef<UGameEventObject> Item, const TSharedRef<STableViewBase>& OwnerTable);

};
