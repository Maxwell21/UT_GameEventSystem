/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#include "GameEventFactory.h"
#include "GameEvent.h"
#include "KismetEditorUtilities.h"

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
	UBlueprint* Blueprint = FKismetEditorUtilities::CreateBlueprint(Class, InParent, Name, BPTYPE_Normal, UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), TEXT("AssetTypeActions"));
	if (UGameEvent* NewGameEvent = Cast<UGameEvent>(Blueprint->GeneratedClass->GetDefaultObject()))
		NewGameEvent->Id = FGuid::NewGuid();

	return Blueprint;
}

#undef LOCTEXT_NAMESPACE
