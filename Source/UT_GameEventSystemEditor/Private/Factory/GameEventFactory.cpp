/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#include "GameEventFactory.h"
#include "GameEvent.h"

#include "GameplayTagsManager.h"
#include "GameplayTagContainer.h"

#include "ModuleManager.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "PropertyCustomizationHelpers.h"
#include "Editor.h"
#include "KismetEditorUtilities.h"
#include "Engine/DataTable.h"

#include "Widgets/Layout/SBorder.h"
#include "STextBlock.h"
#include "SEditableText.h"
#include "SEditableTextBox.h"
#include "SBox.h"
#include "SButton.h"

#define LOCTEXT_NAMESPACE "GameEvent"

/************************************************************************/
/* SGameEventSetupFactory                                               */
/************************************************************************/

void SGameEventSetupFactory::Construct(const FArguments& InArgs)
{
	this->PropertiesConfigured = false;
	this->ActivateTag  = "Activated";
	this->CompleteTag  = "Completed";
	this->CancelTag    = "Canceled";
	this->Factory	   = InArgs._Factory;

	if (!this->Factory)
		return;

	ChildSlot
	.VAlign(VAlign_Fill)
	.HAlign(HAlign_Fill)
	[
		SNew(SVerticalBox)
		+SVerticalBox::Slot()
		.AutoHeight()
		.Padding(10.f, 10.f)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.FillWidth(1.f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("GameEventFactory_NameLabel", "Event Name"))
			]
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Right)
			[
				SNew(SBox)
				.MinDesiredWidth(70.f)
				[
					SNew(SEditableTextBox)
					.Text(LOCTEXT("GameEventFactory_Name", ""))
					.OnTextChanged(this, &SGameEventSetupFactory::OnGameEventNameChanged)
					.SelectAllTextWhenFocused(true)
					.RevertTextOnEscape(true)
				]
			]
		]
		+SVerticalBox::Slot()
		.AutoHeight()
		.Padding(10.f, 10.f)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.FillWidth(1.f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("GameEventFactory_ActivateTagLabel", "Require tag for activate this event"))
			]
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Right)
			[
				SNew(SBox)
				.MinDesiredWidth(70.f)
				[
					SNew(SEditableTextBox)
					.Text(FText::FromName(ActivateTag))
					.OnTextChanged(this, &SGameEventSetupFactory::OnGameEventActivateTagChanged)
					.SelectAllTextWhenFocused(true)
					.RevertTextOnEscape(true)
				]
			]
		]
		+SVerticalBox::Slot()
		.AutoHeight()
		.Padding(10.f, 10.f)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.FillWidth(1.f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("GameEventFactory_CompleteTagLabel", "Tag automatically added when this event is complete"))
			]
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Right)
			.FillWidth(0.3f)
			[
				SNew(SBox)
				.MinDesiredWidth(70.f)
				[
					SNew(SEditableTextBox)
					.Text(FText::FromName(CompleteTag))
					.OnTextChanged(this, &SGameEventSetupFactory::OnGameEventCompleteTagChanged)
					.SelectAllTextWhenFocused(true)
					.RevertTextOnEscape(true)
				]
			]
		]
		+SVerticalBox::Slot()
		.AutoHeight()
		.Padding(10.f, 10.f)
		[
			SNew(SHorizontalBox)
			+SHorizontalBox::Slot()
			.FillWidth(1.f)
			[
				SNew(STextBlock)
				.Text(LOCTEXT("GameEventFactory_CancelTagLabel", "Require tag for cancel this event"))
			]
			+SHorizontalBox::Slot()
			.HAlign(HAlign_Right)
			[
				SNew(SBox)
				.MinDesiredWidth(70.f)
				[
					SNew(SEditableTextBox)
					.Text(FText::FromName(CancelTag))
					.OnTextChanged(this, &SGameEventSetupFactory::OnGameEventCancelTagChanged)
					.SelectAllTextWhenFocused(true)
					.RevertTextOnEscape(true)
				]
			]
		]
		+SVerticalBox::Slot()
		.AutoHeight()
		.Padding(0, 10, 0, 0)
		.HAlign(HAlign_Right)
		[
			SNew(SButton)
			.ButtonStyle(FEditorStyle::Get(), "FlatButton.Success")
			.OnClicked(this, &SGameEventSetupFactory::AddButtonClicked)
			.ContentPadding(FMargin(5, 5, 5, 5))
			.HAlign(EHorizontalAlignment::HAlign_Center)
			[
				SNew(SHorizontalBox)

				+SHorizontalBox::Slot()
				.VAlign(VAlign_Center)
				.AutoWidth()
				.Padding(0, 0, 2, 0)
				[
					SNew(STextBlock)
					.TextStyle(FEditorStyle::Get(), "NormalText.Important")
					.Font(FEditorStyle::Get().GetFontStyle("FontAwesome.10"))
					.Text(FText::FromString(FString(TEXT("\xf067"))) /*fa-plus*/)
				]

				+SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(STextBlock)
					.ColorAndOpacity(FLinearColor::White)
					.Text(LOCTEXT("CreateNewGameEventButton", "Create new GameEvent"))
				]
			]
		]
	];
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

FReply SGameEventSetupFactory::AddButtonClicked()
{
	if (this->IsValid() && this->Factory && this->Factory->GameplayTagDatatable)
	{
		PropertiesConfigured = true;
		this->Factory->Window->RequestDestroyWindow();
	}

	return FReply::Handled();
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
	// GameEventSetupWidget
	GESetup = SNew(SGameEventSetupFactory)
		.Factory(this);

	// Load the content browser module to display an asset picker
	FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	FAssetPickerConfig AssetPickerConfig;

	/** The asset picker will only show datatable */
	AssetPickerConfig.Filter.ClassNames.Add(UDataTable::StaticClass()->GetFName());
	AssetPickerConfig.Filter.bRecursiveClasses = true;

	/** The delegate that fires when an asset was selected */
	AssetPickerConfig.OnAssetSelected = FOnAssetSelected::CreateUObject(this, &UGameEventFactory::OnTargetDatatableSelected);

	/** The default view mode should be a list view */
	AssetPickerConfig.InitialAssetViewType = EAssetViewType::List;

	Window = SNew(SWindow)
		.Title(LOCTEXT("CreateGameEventOptions", "Game Event Setup"))
		.SizingRule(ESizingRule::Autosized)
		.SupportsMinimize(false)
		.SupportsMaximize(false)
		[
			SNew(SBorder)
			.BorderImage(FEditorStyle::GetBrush("Menu.Background"))
			[
				SNew(SVerticalBox)
				+SVerticalBox::Slot()
				.AutoHeight()
				.Padding(10.f, 10.f)
				[
					ContentBrowserModule.Get().CreateAssetPicker(AssetPickerConfig)
				]
				+SVerticalBox::Slot()
				.AutoHeight()
				.Padding(10.f, 10.f)
				[
					GESetup.ToSharedRef()
				]
			]
		];

	GEditor->EditorAddModalWindow(Window.ToSharedRef());
	Window.Reset();

	return GESetup->PropertiesConfigured;
}

UObject* UGameEventFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) 
{
	check(Class->IsChildOf(UGameEvent::StaticClass()));

	if (!this->GESetup->IsValid() || !this->GameplayTagDatatable)
		return nullptr;

	UBlueprint* Blueprint = FKismetEditorUtilities::CreateBlueprint(Class, InParent, Name, BPTYPE_Normal, UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), TEXT("AssetTypeActions"));
	if (UGameEvent* NewGameEvent = Cast<UGameEvent>(Blueprint->GeneratedClass->GetDefaultObject()))
	{
		UGameplayTagsManager& TagManager = UGameplayTagsManager::Get();
		TagManager.LoadGameplayTagTables();

		NewGameEvent->Id = FGuid::NewGuid();
		NewGameEvent->Name = this->GESetup->Name;

		const FString Prefix = "GES." + NewGameEvent->Name.ToString() + ".";

		const FName ActivateTagName = *FString(Prefix + this->GESetup->ActivateTag.ToString());
		const FName CancelTagName = *FString(Prefix + this->GESetup->CancelTag.ToString());
		const FName CompleteTagName = *FString(Prefix + this->GESetup->CompleteTag.ToString());
	
		this->GameplayTagDatatable->AddRow(ActivateTagName, FGameplayTagTableRow(ActivateTagName, ""));
		this->GameplayTagDatatable->AddRow(CancelTagName, FGameplayTagTableRow(CancelTagName, ""));
		this->GameplayTagDatatable->AddRow(CompleteTagName, FGameplayTagTableRow(CompleteTagName, ""));
		this->GameplayTagDatatable->MarkPackageDirty();

		TagManager.EditorRefreshGameplayTagTree();
		FGameplayTag ActivateTag = TagManager.RequestGameplayTag(ActivateTagName);
		FGameplayTag CancelTag = TagManager.RequestGameplayTag(CancelTagName);
		FGameplayTag CompleteTag = TagManager.RequestGameplayTag(CompleteTagName);

		NewGameEvent->AddOnActivate.AddTag(ActivateTag);
		NewGameEvent->CancelStatus.AddTag(CancelTag);
		NewGameEvent->CompleteStatus.AddTag(CompleteTag);

		return Blueprint;
	}

	return nullptr;
}

void UGameEventFactory::OnTargetDatatableSelected(const FAssetData& SelectedAsset)
{
	this->GameplayTagDatatable = Cast<UDataTable>(SelectedAsset.GetAsset());
	if (this->GameplayTagDatatable->RowStruct->GetClass() != FGameplayTagTableRow::StaticStruct()->GetClass())
		this->GameplayTagDatatable = nullptr;
}

#undef LOCTEXT_NAMESPACE
