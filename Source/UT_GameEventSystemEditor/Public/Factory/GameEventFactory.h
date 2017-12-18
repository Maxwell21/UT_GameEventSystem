/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "SlateFwd.h"
#include "Widgets/DeclarativeSyntaxSupport.h"
#include "Widgets/SWindow.h"
#include "Widgets/SCompoundWidget.h"
#include "Reply.h"
#include "UObject/ObjectMacros.h"
#include "Factories/Factory.h"
#include "GameEventFactory.generated.h"

struct FAssetData;
class UDataTable;

#define LOCTEXT_NAMESPACE "GameEvent"

class SGameEventSetupFactory : public SCompoundWidget
{

public:

	SLATE_BEGIN_ARGS(SGameEventSetupFactory)
	{}
		SLATE_ARGUMENT(class UGameEventFactory*, Factory)
	SLATE_END_ARGS()

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

	bool PropertiesConfigured;

	class UGameEventFactory* Factory;

	FText Name;

	FName ActivateTag;

	FName CompleteTag;

	FName CancelTag;


public:

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
		return !this->Name.ToString().IsEmpty()
			&& !this->ActivateTag.IsNone()
			&& !this->CompleteTag.IsNone()
			&& !this->CancelTag.IsNone()
		;
	};

	/************************************************************************/
	/* DELEGATES                                                            */
	/************************************************************************/

	void OnGameEventNameChanged(const FText& NewText);

	void OnGameEventActivateTagChanged(const FText& NewText);

	void OnGameEventCompleteTagChanged(const FText& NewText);

	void OnGameEventCancelTagChanged(const FText& NewText);

	FReply AddButtonClicked();

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

public:

	TSharedPtr<SWindow> Window;

	UPROPERTY()
	UDataTable* GameplayTagDatatable;


	/************************************************************************/
	/* METHODS                                                              */
	/************************************************************************/

	UGameEventFactory(const class FObjectInitializer& Object);

	virtual bool ConfigureProperties() override;

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

	/************************************************************************/
	/* DELEGATES                                                            */
	/************************************************************************/

	void OnTargetDatatableSelected(const FAssetData& SelectedAsset);

};

#undef LOCTEXT_NAMESPACE
