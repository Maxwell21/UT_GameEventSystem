/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Tasks/GameEventTask.h"
#include "GameEventTask_Timer.generated.h"

class UGameEvent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitTimerFinishDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FWaitTimerDelegate, float, TimeElapsed);

/**
 *
 */
UCLASS()
class UT_GAMEEVENTSYSTEM_API UGameEventTask_Timer : public UGameEventTask
{
	GENERATED_BODY()

public:

	static const float TASK_TIME_LIMIT;

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

protected:

	float Time;
	float RestartAt;
	float TimeElapsed;
	bool Complete;

	UPROPERTY()
	FTimerHandle TimerHandle;

	UPROPERTY(BlueprintAssignable)
	FWaitTimerDelegate OnUpdate;

	UPROPERTY(BlueprintAssignable)
	FWaitTimerFinishDelegate OnFinish;


	/************************************************************************/
	/* METHODS                                                              */
	/************************************************************************/

public:

	void Initialize(float InTime, float InRestartAt);

protected:

	/** loop specified time. This is functionally the same as a standard Timer node. */
	UFUNCTION(BlueprintCallable, Category = "Game Event|Tasks", meta = (HidePin = "OwningGameEvent", DefaultToSelf = "OwningGameEvent", BlueprintInternalUseOnly = "TRUE"))
	static UGameEventTask_Timer* Timer(UGameEvent* OwningGameEvent, float Time, float RestartAt = 30.f);

	virtual void Activate() override;

	void OnUpdateTimer();

	void OnFinishTimer();

	virtual void OnDestroy(bool bInOwnerFinished);

};
