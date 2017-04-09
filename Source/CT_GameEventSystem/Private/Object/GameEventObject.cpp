#include "CT_GameEventSystem.h"
#include "GameEventObject.h"
#include "GameEvent.h"
#include "Behavior/GameEventBehavior.h"
#include "GameEventContainerObject.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Component/GameEventComponent.h"

void UGameEventObject::Init(UGameEventContainerObject* GameEventContainerObjectInstance)
{
	this->GameEventContainerObject = GameEventContainerObjectInstance;
}

bool UGameEventObject::MatchEventsTags(FGameplayTagContainer EventsTags)
{
	return this->GameEvent->ActivationRequire.HasAnyExact(EventsTags);
}

bool UGameEventObject::TryActivate()
{
	// check if the event is able to activate
	if (this->IsAbleActivate())
	{
		// add all tags to the current tags
		for (FGameplayTag const& GameplayTag : this->GameEvent->AddOnActivate)
		{
			this->CurrentTags.AddTag(GameplayTag);
		}

		// all tags is added ? 
		if (!this->CurrentTags.IsEmpty())
		{
			// if contain an event behavior instantiate it
			if (this->GameEvent->GameEventBehaviorClass)
			{
				this->GameEventBehavior = NewObject<UGameEventBehavior>(this, this->GameEvent->GameEventBehaviorClass);
				if (this->GameEventBehavior)
				{
					// add this object as owner 
					this->GameEventBehavior->Owner = this;
					this->GameEventBehavior->OnActivated();
				}
			}

			// inform all components listeners
			this->TryActivateAllComponents();

			return true;
		}
	}

	return false;
}

void UGameEventObject::PerformCompleteState()
{
	// Add "CompleteStatus"
	for (FGameplayTag const& GameplayTag : this->GameEvent->CompleteStatus)
	{
		this->CurrentTags.AddTag(GameplayTag);
	}

	// Remove "AddOnActivate"
	for (FGameplayTag const& GameplayTag : this->GameEvent->AddOnActivate)
	{
		this->CurrentTags.RemoveTag(GameplayTag);
	}

	if (this->GameEventBehavior)
		this->GameEventBehavior->OnCompleted();

	this->TryActivateOtherEvents();
}

bool UGameEventObject::IsActive()
{
	return this->CurrentTags.HasAnyExact(this->GameEvent->AddOnActivate) && !this->CurrentTags.HasAnyExact(this->GameEvent->CompleteStatus);
}

void UGameEventObject::AddCustomTags(FGameplayTagContainer Tags)
{
	for (FGameplayTag const& GameplayTag : Tags)
	{
		this->CurrentTags.AddTag(GameplayTag);
	}
}

void UGameEventObject::RemoveCustomTags(FGameplayTagContainer Tags)
{
	for (FGameplayTag const& GameplayTag : Tags)
	{
		this->CurrentTags.RemoveTag(GameplayTag);
	}
}

void UGameEventObject::TryActivateOtherEvents()
{
	if (this->GameEventContainerObject && this->GameEventContainerObject->GameEventManager)
	{
		this->GameEventContainerObject->GameEventManager->TryActivateEvents(this->GameEvent->TryActivateEventOnComplete);
	}
}

bool UGameEventObject::IsAbleActivate()
{
	return !this->CurrentTags.HasAnyExact(this->GameEvent->AddOnActivate) && !this->CurrentTags.HasAnyExact(this->GameEvent->CompleteStatus);
}

void UGameEventObject::TryActivateAllComponents()
{
	if (this->GameEventContainerObject && this->GameEventContainerObject->GameEventManager)
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(this->GameEventContainerObject->GameEventManager, AActor::StaticClass(), Actors);

		for (AActor* const& Actor : Actors)
		{
			if (UGameEventComponent* GameEventComponent = Cast<UGameEventComponent>(Actor->GetComponentByClass(UGameEventComponent::StaticClass())))
			{
				if (GameEventComponent->TagsListener.HasAnyExact(this->CurrentTags) && GameEventComponent->OnGameEventActivate.IsBound())
					GameEventComponent->OnGameEventActivate.Broadcast(this, this->GameEventContainerObject->GameEventManager);
			}
		}
	}
}

