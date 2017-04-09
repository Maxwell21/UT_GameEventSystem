#include "CT_GameEventSystem.h"
#include "GameEventManager.h"
#include "Object/GameEventContainerObject.h"
#include "Object/GameEventObject.h"

// Sets default values
AGameEventManager::AGameEventManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void AGameEventManager::Init()
{
	if (this->GameEventContainer == nullptr)
	{
		this->GameEventContainer = NewObject<UGameEventContainerObject>();
		if (this->GameEventContainer)
			this->GameEventContainer->Init(this->GameEventContainerBase, this);
	}
}

// Called when the game starts or when spawned
void AGameEventManager::BeginPlay()
{
	Super::BeginPlay();	

	this->Init();
}

void AGameEventManager::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	this->GameEventContainer->ConditionalBeginDestroy();
	this->GameEventContainer = nullptr;
	UWorld* World = GetWorld();
	if (World)
		World->ForceGarbageCollection(true);

	Super::EndPlay(EndPlayReason);
}

bool AGameEventManager::TryActivateEvents(FGameplayTagContainer EventsTags)
{
	this->Init();

	if (this->GameEventContainer == nullptr)
		return false;

	bool HasActivatedEvents = false;
	for (UGameEventObject* const& GameEvent : this->GameEventContainer->GameEvents)
	{
		if (GameEvent->MatchEventsTags(EventsTags))
		{
			bool HasActivated = GameEvent->TryActivate();

			if (HasActivated)
				HasActivatedEvents = true;
		}
	}

	return HasActivatedEvents;
}

UGameEventObject* AGameEventManager::GetGameEventById(FGuid Id)
{
	if (this->GameEventContainer)
	{
		for (UGameEventObject* const& GameEventObject : this->GameEventContainer->GameEvents)
		{
			if (GameEventObject->GameEvent->Id == Id && GameEventObject->IsActive())
				return GameEventObject;
		}
	}

	return nullptr;
}

void AGameEventManager::AddCustomTagsToEvent(FGameplayTagContainer CustomTags, UGameEventObject* GameEvent)
{
	if (GameEvent)
		GameEvent->AddCustomTags(CustomTags);
}

void AGameEventManager::RemoveCustomTagsToEvent(FGameplayTagContainer CustomTags, UGameEventObject* GameEvent)
{
	if (GameEvent)
		GameEvent->RemoveCustomTags(CustomTags);
}
