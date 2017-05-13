#pragma once

#include "UObject/NoExportTypes.h"
#include "GameEventContainerObject.generated.h"

class UGameEventContainer;
class UGameEvent;
class AGameEventManager;

/**
 * 
 */
UCLASS()
class CT_GAMEEVENTSYSTEM_API UGameEventContainerObject : public UObject
{
	GENERATED_BODY()

public:

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

	UPROPERTY(Category = "Game Event Container", BlueprintReadWrite)
	TArray<UGameEvent*> GameEvents;

	UPROPERTY()
	AGameEventManager* GameEventManager;

	/************************************************************************/
	/* METHODS                                                              */
	/************************************************************************/

	virtual void Init(UGameEventContainer* GameEventContainer, AGameEventManager* GameEventManagerInstance);

};
