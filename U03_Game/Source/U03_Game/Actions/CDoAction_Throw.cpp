#include "CDoAction_Throw.h"
#include "Global.h"
#include "GameFramework/Character.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "CAim.h"

void ACDoAction_Throw::BeginPlay()
{
	Super::BeginPlay();

	Aim = NewObject<UCAim>();
	Aim->BeginPlay(OwnerCharacter);
}

void ACDoAction_Throw::DoAction()
{
	CheckFalse(State->IsIdleMode());
	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);

	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Throw::Begin_DoAction()
{
}

void ACDoAction_Throw::End_DoAction()
{
	State->SetIdleMode();
	Status->SetMove();
}

void ACDoAction_Throw::Tick(float DeltaTime)
{
}

void ACDoAction_Throw::OnAim()
{
	Aim->On();
}

void ACDoAction_Throw::OffAim()
{
	Aim->Off();
}
