#pragma once

#include "UObject/NoExportTypes.h"
#include "GameplayTagContainer.h"
#include "GameEventObject.generated.h"

class UGameEvent;
class UGameEventBehavior;
class UGameEventContainerObject; 

/**
 * 
 */
UCLASS()
class CT_GAMEEVENTSYSTEM_API UGameEventObject : public UObject
{
	GENERATED_BODY()

public:

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

	/**
	* DataAsset data reference
	*/
	UPROPERTY(Category = "Game Event", BlueprintReadWrite)
	UGameEvent* GameEvent;
	
	/**
	* Current Game Event tags
	*/
	UPROPERTY(Category = "Game Event", BlueprintReadOnly)
	FGameplayTagContainer CurrentTags;

	/**
	* Game event behavior current instance (delete when the GameEvent is complete)
	*/
	UPROPERTY(Category = "Game Event", BlueprintReadOnly, meta = (DisplayName = "Game Event Behavior"))
	UGameEventBehavior* GameEventBehavior;
	
	UPROPERTY()
	UGameEventContainerObject* GameEventContainerObject;

	/************************************************************************/
	/* METHODS                                                              */
	/************************************************************************/
	
	virtual void Init(UGameEventContainerObject* GameEventContainerObjectInstance);

	/**
	* Check if the tag container given match with the "ActivationRequire" tag container
	*
	* @param FGameplayTagContainer EventsTags - the container to compare
	*
	* @return bool - true if match, false otherwise
	*/
	virtual bool MatchEventsTags(FGameplayTagContainer EventsTags);

	/**
	* Try activate if the CurrentTags does not contains the "AddOnActivate" tags
	*
	* @return bool - true if activate, false otherwise
	*/
	virtual bool TryActivate();

	/**
	* Add the "CompleteStatus" tags to the CurrentTags container and call the OnCompleted method
	*/
	virtual void PerformCompleteState();
	
	/**
	* Check if this event is active
	*
	* @return bool - true if active, false otherwise
	*/
	virtual bool IsActive();

	/**
	* Add custom tag can be useful for system like quest
	* Example: if your UI need to have the active quest selected
	*
	* @param FGameplayTagContainer CustomTags
	*/
 	virtual void AddCustomTags(FGameplayTagContainer Tags);

	/**
	* Remove custom tag
	*
	* @param FGameplayTagContainer CustomTags
	*/
 	virtual void RemoveCustomTags(FGameplayTagContainer Tags);

protected:

	/**
	* Called when the event is complete we check if we can activate others event with the "TryActivateEventOnComplete" property
	*/
	virtual void TryActivateOtherEvents();

	/**
	* Check if the CurrentTags does not contains the "AddOnActivate" tags
	*
	* @return bool - true if able to activate, false otherwise
	*/
	virtual bool IsAbleActivate();

	/**
	* If some GameEventCompoenent listen the same "ActivationRequire" we inform them 
	*/
	virtual void TryActivateAllComponents();

};
