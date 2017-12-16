/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#include "GameEventContainerFactory.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "GameEventContainer.h"

#define LOCTEXT_NAMESPACE "GameEvent"

UGameEventContainerFactory::UGameEventContainerFactory(const class FObjectInitializer& Object) : Super(Object)
{
	SupportedClass = UGameEventContainer::StaticClass();
	bEditAfterNew = true;
	bCreateNew = true;
}

UObject* UGameEventContainerFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(Class->IsChildOf(UGameEventContainer::StaticClass()));
	UGameEventContainer* NewGameEvent = NewObject<UGameEventContainer>(InParent, Class, Name, Flags | RF_Transactional);

	return NewGameEvent;
}

#undef LOCTEXT_NAMESPACE
