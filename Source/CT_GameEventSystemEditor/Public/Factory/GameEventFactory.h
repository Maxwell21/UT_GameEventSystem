#pragma once

#include "Factories/Factory.h"
#include "GameEventFactory.generated.h"

#define LOCTEXT_NAMESPACE "GameEvent"

/**
 * 
 */
UCLASS()
class CT_GAMEEVENTSYSTEMEDITOR_API UGameEventFactory : public UFactory
{
	GENERATED_BODY()

public:

	UGameEventFactory(const class FObjectInitializer& Object);

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	
};

#undef LOCTEXT_NAMESPACE
