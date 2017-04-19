#include "CT_GameEventSystemEditor.h"
#include "GameEventDebuggerTab.h"
#include "SDockTab.h"
#include "SButton.h"
#include "UObjectIterator.h"
#include "GameEventContainerObject.h"
#include "GameEventObject.h"

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
	GameEventDetails =
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		.FillHeight(1.f)
	;

	TSharedRef<SDockTab> SpawnedTab = SNew(SDockTab)
	.TabRole(ETabRole::NomadTab)
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.FillHeight(1.f)
		.Padding(5)
		[
			// Left part
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.FillWidth(.3f)
			[
				// Above block
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.FillHeight(.3f)
				[
					SNew(SBorder)
					[
						SNew(SVerticalBox)
						+SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(STextBlock)
							.Text(FText::FromString(TEXT("Actions")))
							.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 16))
						]
						+SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(SBorder)
						]
						+SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(SButton)
							.HAlign(HAlign_Center)
							.OnClicked_Raw(this, &FGameEventDebuggerTab::OnRefreshList)
							.Text(FText::FromString(TEXT("Refresh")))
						]
					]
				]
				// Below block
				+SVerticalBox::Slot()
				.FillHeight(2.7f)
				[
					SNew(SBorder)
					[
						SNew(SVerticalBox)
						+SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(STextBlock)
							.Text(FText::FromString(TEXT("List of GameEvent")))
							.Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Regular.ttf"), 16))
						]
						+SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(SBorder)
						]
						+SVerticalBox::Slot()
						.FillHeight(1.f)
						[
							SNew(SScrollBox)
							+SScrollBox::Slot()
							[
								SAssignNew(GameEventListView, SListView<TSharedRef<UGameEventObject>>)
								.SelectionMode(ESelectionMode::Single)
								.ListItemsSource(&GameEventListItems)
								.OnSelectionChanged(this, &FGameEventDebuggerTab::OnGameEventSelectionChanged)
								.OnGenerateRow(this, &FGameEventDebuggerTab::ListViewOnGenerateRow)
							]
						]
					]
				]
			]
			// Right part
			+SHorizontalBox::Slot()
			.FillWidth(2.7f)
			[
				SNew(SBorder)
				[
					GameEventDetails.ToSharedRef()
				]
			]
		]
	];

	return SpawnedTab;
}

AGameEventManager* FGameEventDebuggerTab::GetSelectedManager()
{
	for (TObjectIterator<AGameEventManager> It; It; ++It)
	{
		if (It->IsSelected())
		{
			if (AGameEventManager* Ptr = *It)
				return Ptr;
		}
	}

	return nullptr;
}

FReply FGameEventDebuggerTab::OnRefreshList()
{
	if (!GameEventListView->IsPendingRefresh())
		this->DisplayList();

	return FReply::Handled();
}

void FGameEventDebuggerTab::DisplayList()
{
	if (AGameEventManager* GameEventManager = this->GetSelectedManager())
	{
		if (GameEventManager->GameEventContainer)
		{

			TArray<UGameEventObject*> GameEvents = GameEventManager->GameEventContainer->GameEvents;
			if (GameEvents.Num() > 0 && GameEventListItems.Num() == 0)
			{
				GameEventListItems.Empty();
				for (UGameEventObject* const& GameEvent : GameEvents)
				{
					GameEventListItems.Add(MakeShareable(GameEvent));
				}

				GameEventListView->RequestListRefresh();
			}
		}
	} 
}

TSharedRef<ITableRow> FGameEventDebuggerTab::ListViewOnGenerateRow(TSharedRef<UGameEventObject> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	return 
		SNew(STableRow< TSharedPtr<FString> >, OwnerTable)
		[
			SNew(STextBlock).Text(Item->GameEvent->Name)
		];
}

void FGameEventDebuggerTab::OnGameEventSelectionChanged(TSharedPtr<UGameEventObject> InItem, ESelectInfo::Type SelectInfo)
{

	ActivateTagsListItems.Empty();
	for (FGameplayTag Tag : InItem->GameEvent->ActivationRequire)
	{
		FName TagName = Tag.GetTagName();
		ActivateTagsListItems.Add(MakeShareable(new FName(TagName)));
	}

	GameEventDetails = 
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.FillHeight(1.f)
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.FillHeight(1.f)
			[
				SAssignNew(ActivateTagsListView, SListView<TSharedRef<FName>>)
				.SelectionMode(ESelectionMode::None)
				.ListItemsSource(&ActivateTagsListItems)
				.OnGenerateRow(this, &FGameEventDebuggerTab::ListViewActivateTagsOnGenerateRow)
			]
		]
	;
}

TSharedRef<ITableRow> FGameEventDebuggerTab::ListViewActivateTagsOnGenerateRow(TSharedRef<FName> Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	return
		SNew(STableRow< TSharedPtr<FString> >, OwnerTable)
		[
			SNew(STextBlock).Text(FText::FromName(*Item))
		];

}
