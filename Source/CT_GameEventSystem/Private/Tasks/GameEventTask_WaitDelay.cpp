#include "CT_GameEventSystem.h"
#include "GameEventTask_WaitDelay.h"
#include "TimerManager.h"

UGameEventTask_WaitDelay* UGameEventTask_WaitDelay::WaitDelay(UGameEvent* OwningGameEvent, float Time)
{
	auto MyObj = NewAbilityTask<UGameEventTask_WaitDelay>(OwningGameEvent);
	MyObj->DelayTime = Time;
	return MyObj;
}

void UGameEventTask_WaitDelay::Activate()
{
	UWorld* World = GetWorld();

	// Use a dummy timer handle as we don't need to store it for later but we don't need to look for something to clear
	FTimerHandle TimerHandle;
	World->GetTimerManager().SetTimer(TimerHandle, this, &UGameEventTask_WaitDelay::OnTimeFinish, this->DelayTime, false);
}

void UGameEventTask_WaitDelay::OnTimeFinish()
{
	OnFinish.Broadcast();
	EndTask();
}

void UGameEventTask_WaitDelay::OnDestroy(bool bInOwnerFinished)
{
	Super::OnDestroy(bInOwnerFinished);
}
