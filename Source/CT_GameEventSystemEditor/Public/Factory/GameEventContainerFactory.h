#pragma once

#include "Factories/Factory.h"
#include "GameEventContainerFactory.generated.h"

#define LOCTEXT_NAMESPACE "GameEvent"

/**
 * 
 */
UCLASS()
class CT_GAMEEVENTSYSTEMEDITOR_API UGameEventContainerFactory : public UFactory
{
	GENERATED_BODY()

public:

	UGameEventContainerFactory(const class FObjectInitializer& Object);

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
	
};

#undef LOCTEXT_NAMESPACE
