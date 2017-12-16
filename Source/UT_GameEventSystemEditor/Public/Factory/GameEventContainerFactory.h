/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#pragma once

#include "Factories/Factory.h"
#include "GameEventContainerFactory.generated.h"

#define LOCTEXT_NAMESPACE "GameEvent"

/**
 *
 */
UCLASS()
class UT_GAMEEVENTSYSTEMEDITOR_API UGameEventContainerFactory : public UFactory
{
	GENERATED_BODY()

public:

	/************************************************************************/
	/* METHODS                                                              */
	/************************************************************************/

	UGameEventContainerFactory(const class FObjectInitializer& Object);

	virtual UObject* FactoryCreateNew(UClass* Class, UObject* InParent, FName Name, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;

};

#undef LOCTEXT_NAMESPACE
