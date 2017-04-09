#pragma once

#include "Engine/DataAsset.h"
#include "GameEventContainer.generated.h"

class UGameEvent;

/**
 * 
 */
UCLASS()
class CT_GAMEEVENTSYSTEM_API UGameEventContainer : public UDataAsset
{
	GENERATED_BODY()
	
public:

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

	UPROPERTY(Category = "Game Event Container", BlueprintReadWrite, EditDefaultsOnly, meta = (DisplayName = "Game Events"))
	TArray<UGameEvent*> GameEventsBase;

};
