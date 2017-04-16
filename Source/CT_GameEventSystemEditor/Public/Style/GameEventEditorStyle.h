#pragma once

#include "CoreMinimal.h"
#include "Styling/ISlateStyle.h"
#include "Styling/SlateStyle.h"

/**
 * 
 */
class CT_GAMEEVENTSYSTEMEDITOR_API FGameEventEditorStyle
{

	/************************************************************************/
	/* PROPERTIES                                                           */
	/************************************************************************/

private:

	static TSharedPtr< class FSlateStyleSet > StyleSet;

	/************************************************************************/
	/* METHODS                                                              */
	/************************************************************************/

public:

	static void Initialize();

	static void Shutdown();

	static TSharedPtr< class ISlateStyle > Get();

	static FName GetStyleSetName();

private:

	static FString InContent(const FString& RelativePath, const TCHAR* Extension);

};
