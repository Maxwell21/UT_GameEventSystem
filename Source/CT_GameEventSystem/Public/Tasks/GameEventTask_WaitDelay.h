#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Tasks/GameEventTask.h"
#include "GameEventTask_WaitDelay.generated.h"

class UGameEvent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWaitDelayDelegate);

/**
 * 
 */
UCLASS()
class CT_GAMEEVENTSYSTEM_API UGameEventTask_WaitDelay : public UGameEventTask
{
	GENERATED_BODY()

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

public:

	float DelayTime;

protected:

	UPROPERTY(BlueprintAssignable)
	FWaitDelayDelegate OnFinish;

	/************************************************************************/
	/* METHODS                                                              */
	/************************************************************************/

	/** Wait specified time. This is functionally the same as a standard Delay node. */
	UFUNCTION(BlueprintCallable, Category = "Game Event|Tasks", meta = (HidePin = "OwningGameEvent", DefaultToSelf = "OwningGameEvent", BlueprintInternalUseOnly = "TRUE"))
	static UGameEventTask_WaitDelay* WaitDelay(UGameEvent* OwningGameEvent, float Time);

protected:
	
	virtual void Activate() override;

	void OnTimeFinish();

	virtual void OnDestroy(bool bInOwnerFinished);
	
};
