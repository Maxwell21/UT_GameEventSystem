#include "CT_GameEventSystem.h"
#include "GameEventBehavior.h"

bool UGameEventBehavior::CompleteCondition_Implementation()
{
	return false;
}

void UGameEventBehavior::UpdateBehavior()
{
	if (this->CompleteCondition() && this->Owner)
	{
		this->Owner->PerformCompleteState();
	}
}
