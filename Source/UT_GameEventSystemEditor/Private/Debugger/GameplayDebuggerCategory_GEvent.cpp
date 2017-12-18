/************************************************************************/
/* UMBRA TOOLS                                                          */
/* Maxwell - Axel Clerget   											*/
/************************************************************************/

#if WITH_GAMEPLAY_DEBUGGER

#include "GameplayDebuggerCategory_GEvent.h"
#include "GameEventManager.h"
#include "GameEventContainer.h"
#include "GameEvent.h"
#include "DebugRenderSceneProxy.h"

FGameplayDebuggerCategory_GEvent::FGameplayDebuggerCategory_GEvent()
{
}

TSharedRef<FGameplayDebuggerCategory> FGameplayDebuggerCategory_GEvent::MakeInstance()
{
	return MakeShareable(new FGameplayDebuggerCategory_GEvent());
}

void FGameplayDebuggerCategory_GEvent::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	if (DebugActor)
	{
		if (AGameEventManager* GEManager = Cast<AGameEventManager>(DebugActor))
		{
			DataPack.ActiveGameEvents.Empty();
			for (auto const& GameEvent : GEManager->GetActiveGameEvents())
			{
				FRepData::FGameEventDebug GEDebug;
				GEDebug.Name = GameEvent->Name.ToString();

				DataPack.ActiveGameEvents.Add(GEDebug);
			}

			DataPack.CanceledGameEvents.Empty();
			for (auto const& GameEvent : GEManager->GetCancelGameEvents())
			{
				FRepData::FGameEventDebug GEDebug;
				GEDebug.Name = GameEvent->Name.ToString();

				DataPack.CanceledGameEvents.Add(GEDebug);
			}

			DataPack.CompletedGameEvents.Empty();
			for (auto const& GameEvent : GEManager->GetCompleteGameEvents())
			{
				FRepData::FGameEventDebug GEDebug;
				GEDebug.Name = GameEvent->Name.ToString();

				DataPack.CompletedGameEvents.Add(GEDebug);
			}
		}
	}
}

void FGameplayDebuggerCategory_GEvent::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	//DISPLAY ALL ACTIVE EVENTS
	CanvasContext.Printf(TEXT("{blue}ACTIVE GAME EVENTS"));
	CanvasContext.Printf(TEXT("{blue}------------------"));
	CanvasContext.Printf(*FString::Printf(TEXT("{black}Count: {green}%d"), DataPack.ActiveGameEvents.Num()));
	{
		FString NameList = "{black}";
		for (int32 Idx = 0; Idx < DataPack.ActiveGameEvents.Num(); Idx++)
		{
			const FRepData::FGameEventDebug& GEDebug = DataPack.ActiveGameEvents[Idx];
			NameList += *GEDebug.Name;
			if (Idx < DataPack.ActiveGameEvents.Num() - 1)
				NameList += ", ";
		}
		CanvasContext.Printf(*NameList);
	}

	//DISPLAY ALL CANCELED EVENT
	CanvasContext.Printf(TEXT("{blue}CANCEL GAME EVENTS"));
	CanvasContext.Printf(TEXT("{blue}------------------"));
	CanvasContext.Printf(*FString::Printf(TEXT("{black}Count: {green}%d"), DataPack.CanceledGameEvents.Num()));
	{
		FString NameList = "{red}";
		for (int32 Idx = 0; Idx < DataPack.CanceledGameEvents.Num(); Idx++)
		{
			const FRepData::FGameEventDebug& GEDebug = DataPack.CanceledGameEvents[Idx];
			NameList += *GEDebug.Name;
			if (Idx < DataPack.ActiveGameEvents.Num() - 1)
				NameList += ", ";
		}
		CanvasContext.Printf(*NameList);
	}

	//DISPLAY ALL COMPLETED EVENTS
	CanvasContext.Printf(TEXT("{blue}COMPLETE GAME EVENTS"));
	CanvasContext.Printf(TEXT("{blue}------------------"));
	CanvasContext.Printf(*FString::Printf(TEXT("{black}Count: {green}%d"), DataPack.CompletedGameEvents.Num()));
	{
		FString NameList = "{green}";
		for (int32 Idx = 0; Idx < DataPack.CompletedGameEvents.Num(); Idx++)
		{
			const FRepData::FGameEventDebug& GEDebug = DataPack.CompletedGameEvents[Idx];
			NameList += *GEDebug.Name;
			if (Idx < DataPack.ActiveGameEvents.Num() - 1)
				NameList += ", ";
		}
		CanvasContext.Printf(*NameList);
	}
}

#endif
