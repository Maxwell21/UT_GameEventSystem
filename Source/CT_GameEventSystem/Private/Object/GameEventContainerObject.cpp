#include "CT_GameEventSystem.h"
#include "GameEventContainerObject.h"
#include "GameEventContainer.h"
#include "GameEventObject.h"
#include "GameEventManager.h"

void UGameEventContainerObject::Init(UGameEventContainer* GameEventContainer, AGameEventManager* GameEventManagerInstance)
{
	if (GameEventContainer == nullptr || GameEventManagerInstance == nullptr)
		return;

	this->GameEventManager = GameEventManagerInstance;

	for (UGameEvent* const& GameEvent : GameEventContainer->GameEventsBase)
	{
		UGameEventObject* EventObjectInstance = NewObject<UGameEventObject>(this);
		if (EventObjectInstance)
		{
			EventObjectInstance->GameEvent = GameEvent;
			EventObjectInstance->GameEventContainerObject = this;
			this->GameEvents.AddUnique(EventObjectInstance);
		}
	}
}
