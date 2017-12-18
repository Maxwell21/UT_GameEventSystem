/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#include "GameEventContainerObject.h"
#include "GameEventContainer.h"
#include "GameEvent.h"
#include "GameEventManager.h"

void UGameEventContainerObject::Init(UGameEventContainer* GameEventContainer, AGameEventManager* GameEventManagerInstance)
{
	if (GameEventContainer == nullptr || GameEventManagerInstance == nullptr)
		return;

	this->GameEventManager = GameEventManagerInstance;

	for (TSubclassOf<UGameEvent> const& GameEventClass : GameEventContainer->GameEventsBase)
	{
		UGameEvent* EventObjectInstance = NewObject<UGameEvent>(this, GameEventClass);
		if (EventObjectInstance)
		{
			EventObjectInstance->Init(this);
			this->GameEvents.AddUnique(EventObjectInstance);
		}
	}
}
