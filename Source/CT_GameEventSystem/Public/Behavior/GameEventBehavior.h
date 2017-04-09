#pragma once

#include "UObject/NoExportTypes.h"
#include "UObject/ScriptMacros.h"
#include "Object/GameEventObject.h"
#include "GameEventBehavior.generated.h"

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class CT_GAMEEVENTSYSTEM_API UGameEventBehavior : public UObject
{
	GENERATED_BODY()
	
public:

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

	UPROPERTY(Category = "Game Event Container", BlueprintReadWrite)
	UGameEventObject* Owner;

	/************************************************************************/
	/* METHODS                                                              */
	/************************************************************************/

	/**
	* Called when the GameEvent is activate
	*/
	UFUNCTION(Category = "Game Event Behavior", BlueprintCallable, BlueprintImplementableEvent)
	void OnActivated();

	/**
	* Condition to turn the GameEvent to the "CompleteStatus"
	*/
	UFUNCTION(Category = "Game Event Behavior", BlueprintCallable, BlueprintNativeEvent)
	bool CompleteCondition();

	/**
	* Called when the GameEvent is complete
	*/
	UFUNCTION(Category = "Game Event Behavior", BlueprintCallable, BlueprintImplementableEvent)
	void OnCompleted();
	
protected: 

	/**
	* Need to be called each time you want to check if the event is complete
	*/
	UFUNCTION(Category = "Game Event Behavior", BlueprintCallable)
	void UpdateBehavior();

};
