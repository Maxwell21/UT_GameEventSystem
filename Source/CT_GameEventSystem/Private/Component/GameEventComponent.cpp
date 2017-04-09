#include "CT_GameEventSystem.h"
#include "GameEventComponent.h"

// Sets default values for this component's properties
UGameEventComponent::UGameEventComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UGameEventComponent::BeginPlay()
{
	Super::BeginPlay();
}
