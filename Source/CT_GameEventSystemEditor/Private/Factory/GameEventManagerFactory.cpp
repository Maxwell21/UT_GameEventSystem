#include "CT_GameEventSystemEditor.h"
#include "GameEventManagerFactory.h"
#include "Kismet2/KismetEditorUtilities.h"
#include "GameEventManager.h"

#define LOCTEXT_NAMESPACE "GameEvent"

UGameEventManagerFactory::UGameEventManagerFactory(const class FObjectInitializer& Object) : Super(Object)
{
	SupportedClass = AGameEventManager::StaticClass();
	bEditAfterNew = true;
	bCreateNew = true;
}

UObject* UGameEventManagerFactory::FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	check(Class->IsChildOf(AGameEventManager::StaticClass()));
	return FKismetEditorUtilities::CreateBlueprint(Class, InParent, Name, BPTYPE_Normal, UBlueprint::StaticClass(), UBlueprintGeneratedClass::StaticClass(), TEXT("AssetTypeActions"));
}

#undef LOCTEXT_NAMESPACE
