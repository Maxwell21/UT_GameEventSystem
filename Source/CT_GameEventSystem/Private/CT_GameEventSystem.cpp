// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "CT_GameEventSystem.h"

#define LOCTEXT_NAMESPACE "FCT_GameEventSystemModule"

void FCT_GameEventSystemModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FCT_GameEventSystemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FCT_GameEventSystemModule, CT_GameEventSystem)