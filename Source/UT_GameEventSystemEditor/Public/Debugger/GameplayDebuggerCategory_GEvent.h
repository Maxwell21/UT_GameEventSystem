/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#pragma once

#if WITH_GAMEPLAY_DEBUGGER

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayDebuggerCategory.h"

class AACtor;
class AGameEventManager;
class APlayerController;
class FGameplayDebuggerCanvasContext;

/**
 * 
 */
class FGameplayDebuggerCategory_GEvent : public FGameplayDebuggerCategory
{

protected:

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

	struct FRepData
	{
		struct FGameEventDebug
		{
			FString Name;
		};
		TArray<FGameEventDebug> ActiveGameEvents;
		TArray<FGameEventDebug> CanceledGameEvents;
		TArray<FGameEventDebug> CompletedGameEvents;
	};
	FRepData DataPack;


public:

	/************************************************************************/
	/* FUNCTIONS                                                            */
	/************************************************************************/

	FGameplayDebuggerCategory_GEvent();

	/** Creates an instance of this category - will be used on module startup to include our category in the Editor */
	static TSharedRef<FGameplayDebuggerCategory> MakeInstance();

	/** Collects the data we would like to print */
	virtual void CollectData(APlayerController* OwnerPC, AActor* DebugActor) override;

	/** Displays the data we collected in the CollectData function */
	virtual void DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext) override;
		
};

#endif