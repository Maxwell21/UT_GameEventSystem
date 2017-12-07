#include "CT_GameEventSystem.h"
#include "GameEventTask_Timer.h"
#include "TimerManager.h"

const float UGameEventTask_Timer::TASK_TIME_LIMIT = 30.f;

void UGameEventTask_Timer::Initialize(float InTime, float InRestartAt)
{
	this->Time		  = InTime;
	this->RestartAt	  = (InRestartAt > 0) ? InRestartAt : UGameEventTask_Timer::TASK_TIME_LIMIT;
	this->TimeElapsed = 0;
	this->Complete    = false;
}

UGameEventTask_Timer* UGameEventTask_Timer::Timer(UGameEvent* OwningGameEvent, float Time, float RestartAt /*= 30.f*/)
{
	auto MyObj = NewAbilityTask<UGameEventTask_Timer>(OwningGameEvent);
	MyObj->Initialize(Time, RestartAt);

	return MyObj;
}

void UGameEventTask_Timer::Activate()
{
	UWorld* World = GetWorld();
	this->TimerHandle = FTimerHandle();
	World->GetTimerManager().SetTimer(this->TimerHandle, this, &UGameEventTask_Timer::OnUpdateTimer, this->Time, true);
}

void UGameEventTask_Timer::OnUpdateTimer()
{
	if (this->CheckIsCanceled() == false || this->CheckIsComplete() == false)
	{
		this->TimeElapsed += Time;
		this->OnUpdate.Broadcast(this->TimeElapsed);

		if (this->TimeElapsed >= this->RestartAt && this->Complete == false)
		{
			this->Complete = true;
			this->OnFinishTimer();
		}
	}

}

void UGameEventTask_Timer::OnFinishTimer()
{
	this->OnFinish.Broadcast();
	this->EndTask();
}

void UGameEventTask_Timer::OnDestroy(bool bInOwnerFinished)
{
	UWorld* World = GetWorld();
	if (World && this->TimerHandle.IsValid())
		World->GetTimerManager().ClearTimer(this->TimerHandle);

	Super::OnDestroy(bInOwnerFinished);
}
