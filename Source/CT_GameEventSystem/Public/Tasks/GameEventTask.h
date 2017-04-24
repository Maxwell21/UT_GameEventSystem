#pragma once

#include "GameplayTask.h"
#include "GameEventTask.generated.h"

class UGameEvent;

/**
 * 
 */
UCLASS()
class CT_GAMEEVENTSYSTEM_API UGameEventTask : public UGameplayTask
{
	GENERATED_BODY()
	

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

public:

	UPROPERTY()
	UGameEvent* GameEvent;

	/************************************************************************/
	/* METHODS                                                              */
	/************************************************************************/

protected:

	/** Helper function for instantiating and initializing a new task */
	template <class T>
	static T* NewAbilityTask(UGameEvent* ThisGameEvent, FName InstanceName = FName())
	{
		check(ThisGameEvent);

		T* MyObj = NewObject<T>();
		MyObj->InitTask(*ThisGameEvent, ThisGameEvent->GetGameplayTaskDefaultPriority());
		MyObj->InstanceName = InstanceName;
		return MyObj;
	}
};
