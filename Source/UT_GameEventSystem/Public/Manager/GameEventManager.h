/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#pragma once

#include "GameFramework/Actor.h"
#include "GameplayTagContainer.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameEventManager.generated.h"

class UGameEventContainer;
class UGameEventContainerObject;
class UGameEvent;
class UGameplayTasksComponent;

/**
 * Game Event Manager
 * Main object contains events and manipulate them
 */
UCLASS()
class UT_GAMEEVENTSYSTEM_API AGameEventManager : public APawn
{
	GENERATED_BODY()

public:

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

	static AGameEventManager* GameEventManagerInstance;

	UPROPERTY(Category = "Game Event Manager", BlueprintReadWrite, EditDefaultsOnly, meta = (DisplayName = "Game Event Container"))
	UGameEventContainer* GameEventContainerBase;

	UPROPERTY(Category = "Game Event Manager", BlueprintReadWrite)
	UGameEventContainerObject* GameEventContainer;

	UPROPERTY(Category = "Game Event Manager", BlueprintReadWrite, EditDefaultsOnly)
	UGameplayTasksComponent* GameplayTaskComponent;

	/************************************************************************/
	/* METHODS                                                              */
	/************************************************************************/

	// Sets default values for this actor's properties
	AGameEventManager(const FObjectInitializer& Obj);

protected:

	virtual void Init();

public:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/** Overridable function called whenever this actor is being removed from a level */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/**
	* Loop on each GameEvents in the container and check if the EventsTags is matching with the GameEvent
	*
	* @param FGameplayTagContainer EventsTags - EventTags matching to activate
	*
	* @return bool - true if some events has been activated, false otherwise
	*/
	UFUNCTION(Category = "Game Event Manager", BlueprintCallable)
	virtual bool TryActivateEvents(FGameplayTagContainer EventsTags);

	/**
	* Get GameEvent with the Id given
	*
	* @param FGuid Id
	*
	* @return UGameEvent* - Instance found or nullptr
	*/
	UFUNCTION(Category = "Game Event Manager", BlueprintCallable)
	virtual UGameEvent* GetGameEventById(FGuid Id);

	/**
	* Get GameEvent with the key given
	*
	* @param FString Key
	*
	* @return UGameEvent* - Instance found or nullptr
	*/
	UFUNCTION(Category = "Game Event Manager", BlueprintCallable)
	virtual UGameEvent* GetGameEventByKey(FString Key);

	/**
	* Get all active GameEvents
	*
	* @return TArray<UGameEvent*> - Empty array or with valid active GameEvent
	*/
	UFUNCTION(Category = "Game Event Manager", BlueprintCallable)
	virtual TArray<UGameEvent*> GetActiveGameEvents();

	/**
	* Get all complete GameEvents
	*
	* @return TArray<UGameEvent*> - Empty array or with valid complete GameEvent
	*/
	UFUNCTION(Category = "Game Event Manager", BlueprintCallable)
	virtual TArray<UGameEvent*> GetCompleteGameEvents();

	/**
	* Get all GameEvents canceled
	*
	* @return TArray<UGameEvent*> - Empty array or with canceled GameEvent
	*/
	UFUNCTION(Category = "Game Event Manager", BlueprintCallable)
	virtual TArray<UGameEvent*> GetCancelGameEvents();

	/**
	* Add custom tag can be useful for system like quest
	* Example: if your UI need to have the active quest selected
	*
	* @param FGameplayTagContainer CustomTags
	*/
	UFUNCTION(Category = "Game Event Manager", BlueprintCallable)
	virtual void AddCustomTagsToEvent(FGameplayTagContainer CustomTags, UGameEvent* GameEvent);

	/**
	* Remove custom tag
	*
	* @param FGameplayTagContainer CustomTags
	*/
	UFUNCTION(Category = "Game Event Manager", BlueprintCallable)
	virtual void RemoveCustomTagsToEvent(FGameplayTagContainer CustomTags, UGameEvent* GameEvent);

	/**
	* Try cancel active events (automatically called when an events has been activated)
	*
	* @param FGameplayTagContainer CustomTags
	*/
	UFUNCTION(Category = "Game Event Manager", BlueprintCallable)
	virtual void TryCancelEvents(FGameplayTagContainer EventsTags);

	/**
	* Get event manager singleton instance found or nullptr otherwise
	*
	* @param UObject* WorldObjectContext
	*/
	UFUNCTION(Category = "Game Event Manager", BlueprintPure, meta = (CompactNodeTitle = "EventManager", WorldContext = "WorldObjectContext"))
	static inline AGameEventManager* GetEventManager(UObject* WorldObjectContext)
	{
		// We have already instance
		if (AGameEventManager::GameEventManagerInstance)
			return AGameEventManager::GameEventManagerInstance;

		// No valid world ? we quit this method
		if (WorldObjectContext->GetWorld() == nullptr)
			return nullptr;

		// Loop through all managers in the level and return the first found
		for (TActorIterator<AGameEventManager> ActorItr(WorldObjectContext->GetWorld()); ActorItr; ++ActorItr)
		{
			// Store and return instance
			AGameEventManager::GameEventManagerInstance = *ActorItr;
			return AGameEventManager::GameEventManagerInstance;
		}

		// No solution
		return nullptr;
	};
};
