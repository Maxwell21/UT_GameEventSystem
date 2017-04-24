#pragma once

#include "UObject/NoExportTypes.h"
#include "UObject/ScriptMacros.h"
#include "GameplayTagContainer.h"
#include "GameplayTaskOwnerInterface.h"
#include "GameEvent.generated.h"

class UGameEventContainerObject; 
class UGameplayTask;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class CT_GAMEEVENTSYSTEM_API UGameEvent : public UObject, public IGameplayTaskOwnerInterface
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
	* Current Game Event tags
	*/
	UPROPERTY(Category = "Game Event", BlueprintReadOnly)
	FGameplayTagContainer CurrentTags;
	
	UPROPERTY()
	UGameEventContainerObject* GameEventContainerObject;

	UPROPERTY()
	TArray<UGameplayTask*>	ActiveTasks;

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

	/**
	* Called when the GameEvent is activate
	*/
	UFUNCTION(Category = "Game Event", BlueprintCallable, BlueprintImplementableEvent)
	void OnActivated();

	/**
	* Condition to turn the GameEvent to the "CompleteStatus"
	*/
	UFUNCTION(Category = "Game Event", BlueprintCallable, BlueprintNativeEvent)
	bool CompleteCondition();

	/**
	* Called when the GameEvent is complete
	*/
	UFUNCTION(Category = "Game Event", BlueprintCallable, BlueprintImplementableEvent)
	void OnCompleted();

protected:

	/**
	* Need to be called each time you want to check if the event is complete
	*/
	UFUNCTION(Category = "Game Event", BlueprintCallable)
	void UpdateBehavior();

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

	// --------------------------------------
	//	IGameplayTaskOwnerInterface
	// --------------------------------------	
	virtual UGameplayTasksComponent* GetGameplayTasksComponent(const UGameplayTask& Task) const override;
	virtual AActor* GetGameplayTaskOwner(const UGameplayTask* Task) const override;
	virtual AActor* GetGameplayTaskAvatar(const UGameplayTask* Task) const override;
	virtual void OnGameplayTaskInitialized(UGameplayTask& Task) override;
	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual void OnGameplayTaskDeactivated(UGameplayTask& Task) override;

};
