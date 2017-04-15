#pragma once

#include "Factories/Factory.h"
#include "GameEventBehaviorFactory.generated.h"

#define LOCTEXT_NAMESPACE "GameEvent"

/**
 * 
 */
UCLASS()
class CT_GAMEEVENTSYSTEMEDITOR_API UGameEventBehaviorFactory : public UFactory
{
	GENERATED_BODY()

public:

	UGameEventBehaviorFactory(const class FObjectInitializer& Object);

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	
};

#undef LOCTEXT_NAMESPACE
