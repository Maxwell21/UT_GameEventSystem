/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#include "GameEvent.h"
#include "GameEventContainerObject.h"
#include "GameEventTask.h"
#include "GameplayTasksComponent.h"
#include "Component/GameEventComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "UnrealType.h"

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

		// all tags are added ? 
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
	/**
	* Check is contain AddOnActivate tags
	* and is not complete
	* and is not canceled
	*/
	return 
		this->CurrentTags.HasAnyExact(this->AddOnActivate) 
		&& !this->CurrentTags.HasAnyExact(this->CompleteStatus)
		&& !this->IsCancel()
	;
}

bool UGameEvent::IsCancel()
{
	return this->CurrentTags.HasAnyExact(this->CancelStatus);
}

void UGameEvent::SetValueAsBool(FName VariableName, bool Value)
{
	this->SetValueAsProperty<UBoolProperty, bool>(VariableName, Value);
}

void UGameEvent::SetValueAsInt(FName VariableName, int Value)
{
	this->SetValueAsProperty<UIntProperty, int>(VariableName, Value);
}

void UGameEvent::SetValueAsFloat(FName VariableName, float Value)
{
	this->SetValueAsProperty<UFloatProperty, float>(VariableName, Value);
}

void UGameEvent::SetValueAsVector(FName VariableName, FVector Value)
{
	if (FVector* ValuePtr = this->GetValueAsProperty<UStructProperty, FVector>(VariableName))
	{
		ValuePtr->X = Value.X;
		ValuePtr->Y = Value.Y;
		ValuePtr->Z = Value.Z;
		this->UpdateBehavior();
	}
}

void UGameEvent::SetValueAsRotator(FName VariableName, FRotator Value)
{
	if (FRotator* ValuePtr = this->GetValueAsProperty<UStructProperty, FRotator>(VariableName))
	{
		ValuePtr->Pitch = Value.Pitch;
		ValuePtr->Yaw   = Value.Yaw;
		ValuePtr->Roll  = Value.Roll;
		this->UpdateBehavior();
	}
}

void UGameEvent::SetValueAsString(FName VariableName, FString Value)
{
	this->SetValueAsProperty<UStrProperty, FString>(VariableName, Value);
}

void UGameEvent::SetValueAsName(FName VariableName, FName Value)
{
	this->SetValueAsProperty<UNameProperty, FName>(VariableName, Value);
}

void UGameEvent::SetValueAsActor(FName VariableName, AActor* Value)
{
	this->SetValueAsProperty<UObjectProperty, AActor*>(VariableName, Value);
}

void UGameEvent::SetValueAsObject(FName VariableName, UObject* Value)
{
	this->SetValueAsProperty<UObjectProperty, UObject*>(VariableName, Value);
}

bool UGameEvent::IsComplete()
{
	return this->CurrentTags.HasAnyExact(this->CompleteStatus);
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

void UGameEvent::TryCancelEvent(FGameplayTagContainer Tags)
{
	if (this->IsAbleCancel() && this->CancelWithTags.HasAny(Tags))
	{
		for (FGameplayTag const& GameplayTag : this->CancelStatus)
		{
			this->CurrentTags.AddTag(GameplayTag);
		}

		this->PerformCancelEvent();
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

void UGameEvent::CancelEvent()
{
	if (this->IsAbleCancel())
	{
		for (FGameplayTag const& GameplayTag : this->CancelStatus)
		{
			this->CurrentTags.AddTag(GameplayTag);
		}

		this->PerformCancelEvent();
	}
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
	return
		!this->IsActive()
		&& !this->IsCancel()
	;
}

bool UGameEvent::IsAbleCancel()
{
	return !this->IsComplete() && this->IsActive();
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
				if (GameEventComponent->TagsListener.HasAnyExact(this->CurrentTags) && GameEventComponent->OnCall.IsBound())
					GameEventComponent->OnCall.Broadcast(this, this->GameEventContainerObject->GameEventManager);
			}
		}
	}
}

void UGameEvent::DispatchToComponents(FGameplayTagContainer Tags)
{
	if (this->GameEventContainerObject && this->GameEventContainerObject->GameEventManager)
	{
		TArray<AActor*> Actors;
		UGameplayStatics::GetAllActorsOfClass(this->GameEventContainerObject->GameEventManager, AActor::StaticClass(), Actors);

		for (AActor* const& Actor : Actors)
		{
			if (UGameEventComponent* GameEventComponent = Cast<UGameEventComponent>(Actor->GetComponentByClass(UGameEventComponent::StaticClass())))
			{
				if (GameEventComponent->TagsListener.HasAnyExact(Tags) && GameEventComponent->OnCall.IsBound())
					GameEventComponent->OnCall.Broadcast(this, this->GameEventContainerObject->GameEventManager);
			}
		}
	}
}

void UGameEvent::PerformCancelEvent()
{
	this->OnCanceled();
}

// --------------------------------------
//	IGameplayTaskOwnerInterface
// --------------------------------------	

UGameplayTasksComponent* UGameEvent::GetGameplayTasksComponent(const UGameplayTask& Task) const
{
	if (AGameEventManager* GameEventManager = this->GameEventContainerObject->GameEventManager)
		return Cast<UGameplayTasksComponent>(GameEventManager->GetComponentByClass(UGameplayTasksComponent::StaticClass()));

	return nullptr;
}

AActor* UGameEvent::GetGameplayTaskOwner(const UGameplayTask* Task) const
{
	AGameEventManager* GameEventManager = this->GameEventContainerObject->GameEventManager;
	return  GameEventManager;
}

AActor* UGameEvent::GetGameplayTaskAvatar(const UGameplayTask* Task) const
{
	AGameEventManager* GameEventManager = this->GameEventContainerObject->GameEventManager;
	return  GameEventManager;
}

void UGameEvent::OnGameplayTaskInitialized(UGameplayTask& Task)
{
 	UGameEventTask* GameEventTask = Cast<UGameEventTask>(&Task);
 	if (GameEventTask)
 		GameEventTask->GameEvent = this;
}

void UGameEvent::OnGameplayTaskActivated(UGameplayTask& Task)
{
 	ActiveTasks.Add(&Task);
}

void UGameEvent::OnGameplayTaskDeactivated(UGameplayTask& Task)
{
 	ActiveTasks.Remove(&Task);
}
