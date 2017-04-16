#include "CT_GameEventSystemEditor.h"
#include "GameEventEditorStyle.h"
#include "Styling/SlateStyleRegistry.h"
#include "Styling/SlateTypes.h"
#include "EditorStyleSet.h"
#include "Interfaces/IPluginManager.h"
#include "SlateOptMacros.h"

#define IMAGE_PLUGIN_BRUSH( RelativePath, ... ) FSlateImageBrush( FGameEventDebuggerStyle::InContent( RelativePath, ".png" ), __VA_ARGS__ )
#define IMAGE_BRUSH(RelativePath, ...) FSlateImageBrush(StyleSet->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)
#define BOX_BRUSH(RelativePath, ...) FSlateBoxBrush(StyleSet->RootToContentDir(RelativePath, TEXT(".png")), __VA_ARGS__)
#define TTF_FONT(RelativePath, ...) FSlateFontInfo(StyleSet->RootToContentDir(RelativePath, TEXT(".ttf")), __VA_ARGS__)
#define TTF_CORE_FONT(RelativePath, ...) FSlateFontInfo(StyleSet->RootToCoreContentDir(RelativePath, TEXT(".ttf") ), __VA_ARGS__)
#define PLUGIN_BRUSH(RelativePath,...) FSlateImageBrush(FGameEventEditorStyle::InContent(RelativePath,TEXT(".png")),__VA_ARGS__)

TSharedPtr< FSlateStyleSet > FGameEventEditorStyle::StyleSet = nullptr;


TSharedPtr<class ISlateStyle> FGameEventEditorStyle::Get()
{
	return StyleSet;
}

FName FGameEventEditorStyle::GetStyleSetName()
{
	static FName PaperStyleName(TEXT("Game Event Debugger"));
	return PaperStyleName;
}

FString FGameEventEditorStyle::InContent(const FString& RelativePath, const TCHAR* Extension)
{
	static FString ContentDir = IPluginManager::Get().FindPlugin(TEXT("CT_GameEventSystem"))->GetContentDir();
	return (ContentDir / RelativePath) + Extension;
}

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void FGameEventEditorStyle::Initialize()
{
	// Const icon sizes
	const FVector2D Icon8x8(8.0f, 8.0f);
	const FVector2D Icon16x16(16.0f, 16.0f);
	const FVector2D Icon20x20(20.0f, 20.0f);
	const FVector2D Icon40x40(40.0f, 40.0f);

	// Only register once
	if (StyleSet.IsValid())
	{
		return;
	}

	StyleSet = MakeShareable(new FSlateStyleSet(GetStyleSetName()));
	StyleSet->SetContentRoot(IPluginManager::Get().FindPlugin(TEXT("CT_GameEventSystem"))->GetContentDir());
	StyleSet->Set("ClassIcon.CT_GameEventSystem", new PLUGIN_BRUSH(TEXT("Icons/CT_GameEventSystem-16"), Icon16x16));
	StyleSet->Set("ClassThumbnail.CT_GameEventSystem", new PLUGIN_BRUSH(TEXT("Icons/CT_GameEventSystem-40"), Icon40x40));

	const FTextBlockStyle& NormalText = FEditorStyle::Get().GetWidgetStyle<FTextBlockStyle>("NormalText");

	FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

#undef IMAGE_PLUGIN_BRUSH
#undef IMAGE_BRUSH
#undef BOX_BRUSH
#undef TTF_FONT
#undef TTF_CORE_FONT
#undef PLUGIN_BRUSH

void FGameEventEditorStyle::Shutdown()
{
	if (StyleSet.IsValid())
	{
		FSlateStyleRegistry::UnRegisterSlateStyle(*StyleSet.Get());
		ensure(StyleSet.IsUnique());
		StyleSet.Reset();
	}
}
