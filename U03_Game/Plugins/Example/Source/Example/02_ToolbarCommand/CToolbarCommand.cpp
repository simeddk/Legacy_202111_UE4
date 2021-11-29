#include "CToolbarCommand.h"

CToolbarCommand::CToolbarCommand()
	: TCommands
	(
		"NewButton",
		FText::FromString("NewButton"),
		NAME_None,
		FEditorStyle::GetStyleSetName()
	)

{
}

CToolbarCommand::~CToolbarCommand()
{
}

void CToolbarCommand::RegisterCommands()
{
#define LOCTEXT_NAMESPACE "CToolbarCommand"
	UI_COMMAND
	(
		Button,
		"FriendlyName",
		"Description",
		EUserInterfaceActionType::Button,
		FInputGesture()
	);
#undef LOCTEXT_NAMESPACE
}
