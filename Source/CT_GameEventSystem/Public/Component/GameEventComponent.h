#pragma once

#include "Components/ActorComponent.h"
#include "Object/GameEvent.h"
#include "GameEventManager.h"
#include "GameEventComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameEventComponentOnActivate, UGameEvent*, GameEventObject, AGameEventManager*, GameEventManager);

UCLASS( ClassGroup=(CrystalTools), meta=(BlueprintSpawnableComponent) )
class CT_GAMEEVENTSYSTEM_API UGameEventComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

	/**
	* Event tags listener
	*/
	UPROPERTY(Category = "Game Event Component", BlueprintReadOnly, EditDefaultsOnly)
	FGameplayTagContainer TagsListener;

	/**
	* Delegate event called when the GameEvent is activate
	*/
	UPROPERTY(Category = "Game Event Component", BlueprintAssignable, BlueprintReadWrite)
	FGameEventComponentOnActivate OnGameEventActivate;
	
	/************************************************************************/
	/* METHODS                                                              */
	/************************************************************************/

	// Sets default values for this component's properties
	UGameEventComponent();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

};
