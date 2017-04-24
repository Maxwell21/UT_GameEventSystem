#include "CT_GameEventSystem.h"
#include "GameEventTask_Timer.h"
#include "TimerManager.h"

UGameEventTask_Timer* UGameEventTask_Timer::Timer(UGameEvent* OwningGameEvent, float Time, bool Looping /*= true*/)
{
	auto MyObj = NewAbilityTask<UGameEventTask_Timer>(OwningGameEvent);
	MyObj->Time = Time;
	MyObj->Looping = Looping;
	return MyObj;
}

void UGameEventTask_Timer::Activate()
{
	UWorld* World = GetWorld();
	this->TimerHandle = FTimerHandle();
	World->GetTimerManager().SetTimer(this->TimerHandle, this, &UGameEventTask_Timer::OnUpdateTimer, this->Time, this->Looping);
}

void UGameEventTask_Timer::OnUpdateTimer()
{
	this->TimeElapsed += Time;
	this->OnUpdate.Broadcast(this->TimeElapsed);
}

void UGameEventTask_Timer::OnDestroy(bool bInOwnerFinished)
{
	UWorld* World = GetWorld();
	World->GetTimerManager().ClearTimer(this->TimerHandle);
	Super::OnDestroy(bInOwnerFinished);
}
