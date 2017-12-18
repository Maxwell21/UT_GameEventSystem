# UT_GameEventSystem 1.1
A flexible event system in Unreal Engine 4

Based on the powerful "GameplayTags" system, the UT_GameEventSystem can provide a flexible event system.

## Install
Just download the plugin and place it inside "YourProjectUnrealEngine/Plugins/UT_GameEventSystem"

**More info in the [WIKI](https://github.com/Maxwell21/UT_GameEventSystem/wiki)**

## Require
You need to create a list of GameplayTags with a gameplay tag datatable and add the datatable inside you project settings
in the "GameplayTags" part on the "Gameplay Tag table list" property.
Tips: I always use "GES" as first category of my tags path.
example : GES.Event1.Status.Open or GES.Event4.Custom.Selected

## How it's work
The plugin provide you 5 main objects
- GameEvent
- GameEventTask
- GameEventComponent
- GameEventContainer
- GameEventManager

### GameEvent
Type: Object (not spawnable)

Function: Contains all information of an event, like what is require for being activated or what is the status for being status complete, or when the GameEvent is complete it can automatically try activate anothers. It contain also the real behavior, example I have a quest and the goal of this quest is to getting 5 apples, so I can store number of apples pickup inside this object.

### GameEventTask
Type: Object (not spawnable)

Function: A GameEventTask is a sub class of GameplayTask feature, you can call all
GameEventTask inside the GameEvent the plugin provide you some task (Timer, WaitDelay...) but you can also create yours.
The GameplayTask are powerful all tasks are running async.

### GameEventComponent
Type: ActorComponent

Function: The goal of the GameEventComponent is to listen some tags and when a GameEvent has been update and an GameEventComponent listen this GameEvent a delegate event of the GameEventComponent will be called.
It's really useful when you have actors (world object) who listen an event and react when some change happens, for example a quest marker above a character displaying when the GameEvent become active.

### GameEventContainer
Type: DataAsset

Function: Contains only all GameEvent in an array property.

### GameEventManager
Type: Actor

Function: Contain a GameEventContainer and it's the only object manipulator of the Container and their GameEvent.
Can try activate GameEvent, add custom tags to a GameEvent and more.
