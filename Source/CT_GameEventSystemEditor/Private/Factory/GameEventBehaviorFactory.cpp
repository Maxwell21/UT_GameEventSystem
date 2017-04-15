#include "CT_GameEventSystemEditor.h"
#include "GameEventBehaviorFactory.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "GameEventBehavior.h"

#define LOCTEXT_NAMESPACE "GameEvent"

UGameEventBehaviorFactory::UGameEventBehaviorFactory(const class FObjectInitializer& Object) : Super(Object)
{
	SupportedClass = UGameEventBehavior::StaticClass();
	bEditAfterNew = true;
	bCreateNew = true;
}

UObject* UGameEventBehaviorFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(Class->IsChildOf(UGameEventBehavior::StaticClass()));
	return FKismetEditorUtilities::CreateBlueprint(Class, InParent, Name, BPTYPE_Normal, UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), TEXT("AssetTypeActions"));
}

#undef LOCTEXT_NAMESPACE
