#include "CUserWidget_SelectItem.h"
#include "Global.h"
#include "Characters/CPlayer.h"
#include "Widgets/CUserWidget_Select.h"

void UCUserWidget_SelectItem::Click()
{
	GetSelectWidget()->Click(GetName());
}

void UCUserWidget_SelectItem::Hover()
{
	GetSelectWidget()->Hover(GetName());
}

void UCUserWidget_SelectItem::Unhover()
{
	GetSelectWidget()->Unhover(GetName());
}

UCUserWidget_Select* UCUserWidget_SelectItem::GetSelectWidget()
{
	ACPlayer* player = Cast<ACPlayer>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));

	return player->GetSelectWidget();
}
