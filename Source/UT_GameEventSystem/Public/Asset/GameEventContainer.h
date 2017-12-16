/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#pragma once

#include "Engine/DataAsset.h"
#include "GameEvent.h"
#include "GameEventContainer.generated.h"


/**
 * Game Event Container
 * A simple container of your GameEvent
 */
UCLASS()
class UT_GAMEEVENTSYSTEM_API UGameEventContainer : public UDataAsset
{
	GENERATED_BODY()

public:

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

	UPROPERTY(Category = "Game Event Container", BlueprintReadWrite, EditDefaultsOnly, meta = (DisplayName = "Game Events"))
	TArray<TSubclassOf<UGameEvent>> GameEventsBase;

};
