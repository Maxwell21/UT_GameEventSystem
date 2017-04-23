#include "CT_GameEventSystem.h"
#include "GameEvent.h"
#include "GameEventContainerObject.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Component/GameEventComponent.h"

void UGameEvent::Init(UGameEventContainerObject* GameEventContainerObjectInstance)
{
	this->GameEventContainerObject = GameEventContainerObjectInstance;
}

bool UGameEvent::MatchEventsTags(FGameplayTagContainer EventsTags)
{
	return this->ActivationRequire.HasAnyExact(EventsTags);
}

bool UGameEvent::TryActivate()
{
	// check if the event is able to activate
	if (this->IsAbleActivate())
	{
		// add all tags to the current tags
		for (FGameplayTag const& GameplayTag : this->AddOnActivate)
		{
			this->CurrentTags.AddTag(GameplayTag);
		}

		// all tags is added ? 
		if (!this->CurrentTags.IsEmpty())
		{
			// active the event
			this->OnActivated();
			// inform all components listeners
			this->TryActivateAllComponents();

			return true;
		}
	}

	return false;
}

void UGameEvent::PerformCompleteState()
{
	// Add "CompleteStatus"
	for (FGameplayTag const& GameplayTag : this->CompleteStatus)
	{
		this->CurrentTags.AddTag(GameplayTag);
	}

	// Remove "AddOnActivate"
	for (FGameplayTag const& GameplayTag : this->AddOnActivate)
	{
		this->CurrentTags.RemoveTag(GameplayTag);
	}

	this->OnCompleted();

	this->TryActivateOtherEvents();
}

bool UGameEvent::IsActive()
{
	return this->CurrentTags.HasAnyExact(this->AddOnActivate) && !this->CurrentTags.HasAnyExact(this->CompleteStatus);
}

void UGameEvent::AddCustomTags(FGameplayTagContainer Tags)
{
	for (FGameplayTag const& GameplayTag : Tags)
	{
		this->CurrentTags.AddTag(GameplayTag);
	}
}

void UGameEvent::RemoveCustomTags(FGameplayTagContainer Tags)
{
	for (FGameplayTag const& GameplayTag : Tags)
	{
		this->CurrentTags.RemoveTag(GameplayTag);
	}
}

bool UGameEvent::CompleteCondition_Implementation()
{
	return false;
}

void UGameEvent::UpdateBehavior()
{
	if (this->CompleteCondition())
		this->PerformCompleteState();
}

void UGameEvent::TryActivateOtherEvents()
{
	if (this->GameEventContainerObject && this->GameEventContainerObject->GameEventManager)
	{
		this->GameEventContainerObject->GameEventManager->TryActivateEvents(this->TryActivateEventOnComplete);
	}
}

bool UGameEvent::IsAbleActivate()
{
	return !this->CurrentTags.HasAnyExact(this->AddOnActivate) && !this->CurrentTags.HasAnyExact(this->CompleteStatus);
}

void UGameEvent::TryActivateAllComponents()
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

