/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#pragma once

#include "Components/ActorComponent.h"
#include "Object/GameEvent.h"
#include "GameEventManager.h"
#include "GameEventComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGameEventComponentOnCall, UGameEvent*, GameEventObject, AGameEventManager*, GameEventManager);

UCLASS( ClassGroup=(Umbra), meta=(BlueprintSpawnableComponent) )
class UT_GAMEEVENTSYSTEM_API UGameEventComponent : public UActorComponent
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
	* Delegate event called when the listener is called
	*/
	UPROPERTY(Category = "Game Event Component", BlueprintAssignable, BlueprintReadWrite)
	FGameEventComponentOnCall OnCall;

	/************************************************************************/
	/* METHODS                                                              */
	/************************************************************************/

	// Sets default values for this component's properties
	UGameEventComponent();

protected:

	// Called when the game starts
	virtual void BeginPlay() override;

};
