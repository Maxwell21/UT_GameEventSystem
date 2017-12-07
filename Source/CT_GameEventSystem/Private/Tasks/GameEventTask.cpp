#include "CT_GameEventSystem.h"
#include "GameEventTask.h"

bool UGameEventTask::CheckIsCanceled()
{
	if (this->GameEvent && this->GameEvent->IsCancel())
	{
		this->EndTask();
		return true;
	}

	return false;
}

bool UGameEventTask::CheckIsComplete()
{
	if (this->GameEvent && this->GameEvent->IsComplete())
	{
		this->EndTask();
		return true;
	}

	return false;
}
