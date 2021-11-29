#include "CGameplayDebugCategory.h"
#include "GameFramework/PlayerController.h"

CGameplayDebugCategory::CGameplayDebugCategory()
{
	UE_LOG(LogTemp, Error, L"CGameplayDebugCategory Start");
}

CGameplayDebugCategory::~CGameplayDebugCategory()
{
	UE_LOG(LogTemp, Error, L"CGameplayDebugCategory End");
}

TSharedRef<FGameplayDebuggerCategory> CGameplayDebugCategory::MakeInstance()
{
	return MakeShareable(new CGameplayDebugCategory());
}

void CGameplayDebugCategory::CollectData(APlayerController* OwnerPC, AActor* DebugActor)
{
	

	if (!!DebugActor)
	{
		Data.Actor = DebugActor;
		Data.Location = DebugActor->GetActorLocation();
	}

}

void CGameplayDebugCategory::DrawData(APlayerController* OwnerPC, FGameplayDebuggerCanvasContext& CanvasContext)
{
	if (!!Data.Actor)
	{
		//DebugActor�� �̸��� ����^^
		CanvasContext.Printf(FColor(255, 0, 0), L"Name : %s", *Data.Actor->GetName());

		//DebugActor�� ���� ��ġ�� ����^^
		CanvasContext.Printf(FColor(0, 255, 0), L"Location : %s", *Data.Location.ToString());

		//DebugActor�� �÷��̾������ �Ÿ��� ����^^
		CanvasContext.Printf(FColor(0, 0, 255), L"Distance : %.2f", OwnerPC->GetPawn()->GetDistanceTo(Data.Actor));
	}	
}