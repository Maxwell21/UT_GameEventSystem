#pragma once

#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"
#include "Templates/SubclassOf.h"
#include "GameEvent.generated.h"

class UGameEventBehavior;

/**
 * 
 */
UCLASS()
class CT_GAMEEVENTSYSTEM_API UGameEvent : public UDataAsset
{
	GENERATED_BODY()
	
public:

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

	/**
	* Unique Id
	*/
	UPROPERTY(Category = "Game Event", BlueprintReadOnly, EditDefaultsOnly)
	FGuid Id;

	/**
	* Event name
	*/
	UPROPERTY(Category = "Game Event", BlueprintReadOnly, EditDefaultsOnly)
	FText Name;

	/**
	* Event description
	*/
	UPROPERTY(Category = "Game Event", BlueprintReadOnly, EditDefaultsOnly)
	FText Description;

	/**
	* Tags required for activate this event
	*/
	UPROPERTY(Category = "Game Event", BlueprintReadOnly, EditDefaultsOnly)
	FGameplayTagContainer ActivationRequire;

	/**
	* Tags added when the event is activated
	*/
	UPROPERTY(Category = "Game Event", BlueprintReadOnly, EditDefaultsOnly)
	FGameplayTagContainer AddOnActivate;

	/**
	* Checking tags for complete this event
	*/
	UPROPERTY(Category = "Game Event", BlueprintReadOnly, EditDefaultsOnly)
	FGameplayTagContainer CompleteStatus;

	/**
	* When this event is complete we can try to active others
	*/
	UPROPERTY(Category = "Game Event", BlueprintReadOnly, EditDefaultsOnly)
	FGameplayTagContainer TryActivateEventOnComplete;

	/**
	* Game event behavior available while the GameEvent is still activated
	*/
	UPROPERTY(Category = "Game Event", BlueprintReadOnly, EditDefaultsOnly, meta = (DisplayName = "Game Event Behavior"))
	TSubclassOf<UGameEventBehavior> GameEventBehaviorClass;

};
