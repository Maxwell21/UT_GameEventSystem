/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "SlateFwd.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "UObject/ObjectMacros.h"
#include "Factories/Factory.h"
#include "GameEventFactory.generated.h"

struct FAssetData;
class UDataTable;
class SWindow;
class SCompoundWidget;

#define LOCTEXT_NAMESPACE "GameEvent"

class SGameEventSetupFactory : public SCompoundWidget
{

public:

	SLATE_BEGIN_ARGS(SGameEventSetupFactory)
	{}

	SLATE_END_ARGS()

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

	FText Name;

	FName ActivateTag;

	FName CompleteTag;

	FName CancelTag;

	UDataTable* GameplayTagDatatable;

	/************************************************************************/
	/* METHODS                                                              */
	/************************************************************************/
	
	/**
	* Construct this widget
	*
	* @param	InArgs	The declaration data for this widget
	*/
	void Construct(const FArguments& InArgs);

	inline bool IsValid()
	{
		return this->GameplayTagDatatable != nullptr
			&& !this->Name.ToString().IsEmpty()
			&& !this->ActivateTag.IsNone()
			&& !this->CompleteTag.IsNone()
			&& !this->CancelTag.IsNone()
		;
	};


	/************************************************************************/
	/* DELEGATES                                                            */
	/************************************************************************/

	void OnTargetDatatableSelected(const FAssetData& SelectedAsset);

	void OnGameEventNameChanged(const FText& NewText);

	void OnGameEventActivateTagChanged(const FText& NewText);

	void OnGameEventCompleteTagChanged(const FText& NewText);

	void OnGameEventCancelTagChanged(const FText& NewText);

};

/**
 *
 */
UCLASS()
class UT_GAMEEVENTSYSTEMEDITOR_API UGameEventFactory : public UFactory
{
	GENERATED_BODY()

protected:

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

	TSharedPtr<SGameEventSetupFactory> GESetup;

	TSharedPtr<SWindow> PickerWindow;

public:

	/************************************************************************/
	/* METHODS                                                              */
	/************************************************************************/

	UGameEventFactory(const class FObjectInitializer& Object);

	virtual bool ConfigureProperties() override;

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

};

#undef LOCTEXT_NAMESPACE
