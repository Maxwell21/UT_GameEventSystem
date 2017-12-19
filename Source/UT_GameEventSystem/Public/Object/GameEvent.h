/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#pragma once

#include "UObject/NoExportTypes.h"
#include "UObject/ScriptMacros.h"
#include "GameplayTagContainer.h"
#include "GameplayTaskOwnerInterface.h"
#include "GameEvent.generated.h"

class UGameEventContainerObject;
class UGameplayTask;

/**
 * Game Event
 * Flexible game event based on Gameplay Tags
 * All behavior inside this object
 */
UCLASS(BlueprintType, Blueprintable)
class UT_GAMEEVENTSYSTEM_API UGameEvent : public UObject, public IGameplayTaskOwnerInterface
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
	* Unique Key
	*/
	UPROPERTY(Category = "Game Event", BlueprintReadOnly, EditDefaultsOnly)
	FString Key;

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
	* that tags will be added for cancel this event
	*/
	UPROPERTY(Category = "Game Event", BlueprintReadOnly, EditDefaultsOnly)
	FGameplayTagContainer CancelWithTags;

	/**
	* that tags will be added for cancel this event
	*/
	UPROPERTY(Category = "Game Event", BlueprintReadOnly, EditDefaultsOnly)
	FGameplayTagContainer CancelStatus;

	/**
	* Current Game Event tags
	*/
	UPROPERTY(Category = "Game Event", BlueprintReadOnly)
	FGameplayTagContainer CurrentTags;

	UPROPERTY()
	UGameEventContainerObject* GameEventContainerObject;

	/*
	* Current Active tasks related to this GameEvent
	*/
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
	* Check if this event is cancel
	*
	* @return bool - true if cancel, false otherwise
	*/
	UFUNCTION(Category = "Game Event", BlueprintCallable)
	virtual bool IsCancel();

	/**
	* Set value as boolean for the variable given
	* if the variable is not found so the function is canceled
	*
	* @param FName VariableName
	* @param bool Value
	*/
	UFUNCTION(Category = "Game Event", BlueprintCallable)
	virtual void SetValueAsBool(FName VariableName, bool Value);

	/**
	* Set value as integer for the variable given
	* if the variable is not found so the function is canceled
	*
	* @param FName VariableName
	* @param int Value
	*/
	UFUNCTION(Category = "Game Event", BlueprintCallable)
	virtual void SetValueAsInt(FName VariableName, int Value);

	/**
	* Set value as float for the variable given
	* if the variable is not found so the function is canceled
	*
	* @param FName VariableName
	* @param float Value
	*/
	UFUNCTION(Category = "Game Event", BlueprintCallable)
	virtual void SetValueAsFloat(FName VariableName, float Value);
	
	/**
	* Set value as vector for the variable given
	* if the variable is not found so the function is canceled
	*
	* @param FName VariableName
	* @param FVector Value
	*/
	UFUNCTION(Category = "Game Event", BlueprintCallable)
	virtual void SetValueAsVector(FName VariableName, FVector Value);

	/**
	* Set value as rotator for the variable given
	* if the variable is not found so the function is canceled
	*
	* @param FName VariableName
	* @param FRotator Value
	*/
	UFUNCTION(Category = "Game Event", BlueprintCallable)
	virtual void SetValueAsRotator(FName VariableName, FRotator Value);

	/**
	* Set value as string for the variable given
	* if the variable is not found so the function is canceled
	*
	* @param FName VariableName
	* @param FString Value
	*/
	UFUNCTION(Category = "Game Event", BlueprintCallable)
	virtual void SetValueAsString(FName VariableName, FString Value);

	/**
	* Set value as name for the variable given
	* if the variable is not found so the function is canceled
	*
	* @param FName VariableName
	* @param FName Value
	*/
	UFUNCTION(Category = "Game Event", BlueprintCallable)
	virtual void SetValueAsName(FName VariableName, FName Value);

	/**
	* Set value as actor for the variable given
	* if the variable is not found so the function is canceled
	*
	* @param FName VariableName
	* @param AActor* Value
	*/
	UFUNCTION(Category = "Game Event", BlueprintCallable)
	virtual void SetValueAsActor(FName VariableName, AActor* Value);

	/**
	* Set value as object for the variable given
	* if the variable is not found so the function is canceled
	*
	* @param FName VariableName
	* @param UObject* Value
	*/
	UFUNCTION(Category = "Game Event", BlueprintCallable)
	virtual void SetValueAsObject(FName VariableName, UObject* Value);

	/**
	* Check if this event is complete
	*
	* @return bool - true if complete, false otherwise
	*/
	virtual bool IsComplete();

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
	* Cancel this event
	*/
	virtual void TryCancelEvent(FGameplayTagContainer Tags);

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

	/**
	* Called when the GameEvent is cancel
	*/
	UFUNCTION(Category = "Game Event", BlueprintCallable, BlueprintImplementableEvent)
	void OnCanceled();

protected:

	/**
	* Need to be called each time you want to check if the event is complete
	*/
	UFUNCTION(Category = "Game Event", BlueprintCallable)
	void UpdateBehavior();

	/**
	* Cancel this event
	*/
	UFUNCTION(Category = "Game Event", BlueprintCallable)
	virtual void CancelEvent();

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
	* Check if is not complete and is active
	*
	* @return bool - true if able to cancel, false otherwise
	*/
	virtual bool IsAbleCancel();

	/**
	* If some GameEventCompoenent listen the same "ActivationRequire" we inform them
	*/
	virtual void TryActivateAllComponents();

	/**
	* Dispatch and check if components listen tags given
	*
	* @param FGameplayTagContainer Tags - Check if the component is listen that tags
	*/
	UFUNCTION(Category = "Game Event", BlueprintCallable)
	virtual void DispatchToComponents(FGameplayTagContainer Tags);

	/**
	* Set value to the variable given
	*
	* @param FName VariableName
	* @param ValueType Value - template value
	*/
	virtual void PerformCancelEvent();

	/**/
	template<class PropertyType, class ValueType>
	void SetValueAsProperty(FName VariableName, ValueType Value)
	{
		for (TFieldIterator<PropertyType> Property(this->GetClass()); Property; ++Property)
		{
			if (VariableName == *Property->GetName())
			{
				Property->SetPropertyValue_InContainer(this, Value);
				this->UpdateBehavior();
			}
		}

	};

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
