#include "CT_GameEventSystemEditor.h"
#include "GameEventFactory.h"
#include "GameEvent.h"

#define LOCTEXT_NAMESPACE "GameEvent"

UGameEventFactory::UGameEventFactory(const class FObjectInitializer& Object) : Super(Object)
{
	SupportedClass = UGameEvent::StaticClass();
	bEditAfterNew = true;
	bCreateNew = true;
}

UObject* UGameEventFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) 
{
	check(Class->IsChildOf(UGameEvent::StaticClass()));
	UGameEvent* NewGameEvent = NewObject<UGameEvent>(InParent, Class, Name, Flags | RF_Transactional);
	NewGameEvent->Id = FGuid::NewGuid();

	return NewGameEvent;
}

#undef LOCTEXT_NAMESPACE
