/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#include "GameEventFactory.h"
#include "GameEvent.h"

#include "ModuleManager.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "PropertyCustomizationHelpers.h"
#include "Editor.h"
#include "KismetEditorUtilities.h"
#include "Engine/DataTable.h"

#include "Widgets/SWindow.h"
#include "Widgets/SCompoundWidget.h"
#include "Widgets/Layout/SBorder.h"
#include "STextBlock.h"
#include "SEditableText.h"

#define LOCTEXT_NAMESPACE "GameEvent"

/************************************************************************/
/* SGameEventSetupFactory                                               */
/************************************************************************/

void SGameEventSetupFactory::Construct(const FArguments& InArgs)
{
	// Load the content browser module to display an asset picker
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

	FAssetPickerConfig AssetPickerConfig;

	/** The asset picker will only show GameplayTagDatatable */
	AssetPickerConfig.Filter.ClassNames.Add(UDataTable::StaticClass()->GetFName());
	AssetPickerConfig.Filter.bRecursiveClasses = true;

	/** The delegate that fires when an asset was selected */
	//AssetPickerConfig.OnAssetSelected = FOnAssetSelected::CreateUObject(this, &SGameEventSetupFactory::OnTargetDatatableSelected);

	/** The default view mode should be a list view */
	AssetPickerConfig.InitialAssetViewType = EAssetViewType::List;

	ChildSlot
	.VAlign(VAlign_Fill)
	.HAlign(HAlign_Fill)
	[
		SNew(SBorder)
		.BorderImage(FEditorStyle::GetBrush("Menu.Background"))
		[
			SNew(SVerticalBox)
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				ContentBrowserModule.Get().CreateAssetPicker(AssetPickerConfig)
			]
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("GameEventFactory_NameLabel", "Event Name"))
				]
				+SHorizontalBox::Slot()
				[
					SNew(SEditableText)
					.Text(LOCTEXT("GameEventFactory_Name", "My Event"))
					.OnTextChanged(this, &SGameEventSetupFactory::OnGameEventNameChanged)
					.SelectAllTextWhenFocused(true)
					.RevertTextOnEscape(true)
				]
			]
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("GameEventFactory_ActivateTagLabel", "Require tag for activate this event"))
				]
				+SHorizontalBox::Slot()
				[
					SNew(SEditableText)
					.Text(LOCTEXT("GameEventFactory_ActivateTag", "Activated"))
					.OnTextChanged(this, &SGameEventSetupFactory::OnGameEventActivateTagChanged)
					.SelectAllTextWhenFocused(true)
					.RevertTextOnEscape(true)
				]
			]
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("GameEventFactory_CompleteTagLabel", "Tag automatically added when this event is complete"))
				]
				+SHorizontalBox::Slot()
				[
					SNew(SEditableText)
					.Text(LOCTEXT("GameEventFactory_CompleteTag", "Completed"))
					.OnTextChanged(this, &SGameEventSetupFactory::OnGameEventCompleteTagChanged)
					.SelectAllTextWhenFocused(true)
					.RevertTextOnEscape(true)
				]
			]
			+SVerticalBox::Slot()
			.AutoHeight()
			[
				SNew(SHorizontalBox)
				+SHorizontalBox::Slot()
				[
					SNew(STextBlock)
					.Text(LOCTEXT("GameEventFactory_CancelTagLabel", "Require tag for cancel this event"))
				]
				+SHorizontalBox::Slot()
				[
					SNew(SEditableText)
					.Text(LOCTEXT("GameEventFactory_CancelTag", "Cancel"))
					.OnTextChanged(this, &SGameEventSetupFactory::OnGameEventCancelTagChanged)
					.SelectAllTextWhenFocused(true)
					.RevertTextOnEscape(true)
				]
			]
		]
	];
}

void SGameEventSetupFactory::OnTargetDatatableSelected(const FAssetData& SelectedAsset)
{
	this->GameplayTagDatatable = Cast<UDataTable>(SelectedAsset.GetAsset());
}

void SGameEventSetupFactory::OnGameEventNameChanged(const FText& NewText)
{
	this->Name = NewText;
}

void SGameEventSetupFactory::OnGameEventActivateTagChanged(const FText& NewText)
{
	this->ActivateTag = FName(*NewText.ToString());
}

void SGameEventSetupFactory::OnGameEventCompleteTagChanged(const FText& NewText)
{
	this->CompleteTag = FName(*NewText.ToString());
}

void SGameEventSetupFactory::OnGameEventCancelTagChanged(const FText& NewText)
{
	this->CancelTag = FName(*NewText.ToString());
}

/************************************************************************/
/* UGameEventFactory                                                    */
/************************************************************************/

UGameEventFactory::UGameEventFactory(const class FObjectInitializer& Object) : Super(Object)
{
	SupportedClass = UGameEvent::StaticClass();
	bEditAfterNew = true;
	bCreateNew = true;
}

bool UGameEventFactory::ConfigureProperties()
{
	TSharedRef<SGameEventSetupFactory> GameEventFactoryWidget = SNew(SGameEventSetupFactory);
	this->GESetup = GameEventFactoryWidget;

	PickerWindow = SNew(SWindow)
		.Title(LOCTEXT("CreateGameEventOptions", "Game Event Setup"))
		.ClientSize(FVector2D(500, 600))
		.SupportsMinimize(false).SupportsMaximize(false)
		[
			GameEventFactoryWidget->AsShared()
		];

	GEditor->EditorAddModalWindow(PickerWindow.ToSharedRef());
	PickerWindow.Reset();

	//return this->GESetup->IsValid();

	return false;
}

UObject* UGameEventFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) 
{
	check(Class->IsChildOf(UGameEvent::StaticClass()));

	UBlueprint* Blueprint = FKismetEditorUtilities::CreateBlueprint(Class, InParent, Name, BPTYPE_Normal, UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), TEXT("AssetTypeActions"));
	if (UGameEvent* NewGameEvent = Cast<UGameEvent>(Blueprint->GeneratedClass->GetDefaultObject()))
		NewGameEvent->Id = FGuid::NewGuid();

	return Blueprint;
}

#undef LOCTEXT_NAMESPACE
