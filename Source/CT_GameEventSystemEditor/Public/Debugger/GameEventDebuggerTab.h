#pragma once

#include "CoreMinimal.h"
#include "TabManager.h"
#include "GameEventManager.h"
#include "Input/Reply.h"
#include "SListView.h"
#include "SharedPointer.h"
#include "GameplayTagContainer.h"

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

	TSharedPtr<SVerticalBox> GameEventDetails;

	/** The list view widget for our activate tags list */
	TSharedPtr<SListView<TSharedRef<FName>>> ActivateTagsListView;

	/** List of everything that we want to display */
	TArray<TSharedRef<FName>> ActivateTagsListItems;

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

	void OnGameEventSelectionChanged(TSharedPtr<UGameEventObject> InItem, ESelectInfo::Type SelectInfo);

	TSharedRef<ITableRow> ListViewActivateTagsOnGenerateRow(TSharedRef<FName> Item, const TSharedRef<STableViewBase>& OwnerTable);

};
