#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Tasks/GameEventTask.h"
#include "GameEventTask_Timer.generated.h"

class UGameEvent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitTimerDelegate, float, TimeElapsed);

/**
 * 
 */
UCLASS()
class CT_GAMEEVENTSYSTEM_API UGameEventTask_Timer : public UGameEventTask
{
	GENERATED_BODY()

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

public:

	float Time;
	
	float TimeElapsed;

	bool Looping;

protected: 

	UPROPERTY()
	FTimerHandle TimerHandle;

	UPROPERTY(BlueprintAssignable)
	FWaitTimerDelegate OnUpdate;

	/************************************************************************/
	/* METHODS                                                              */
	/************************************************************************/

	/** loop specified time. This is functionally the same as a standard Timer node. */
	UFUNCTION(BlueprintCallable, Category = "Game Event|Tasks", meta = (HidePin = "OwningGameEvent", DefaultToSelf = "OwningGameEvent", BlueprintInternalUseOnly = "TRUE"))
	static UGameEventTask_Timer* Timer(UGameEvent* OwningGameEvent, float Time, bool Looping = true);

protected:

	virtual void Activate() override;

	void OnUpdateTimer();

	virtual void OnDestroy(bool bInOwnerFinished);

};
