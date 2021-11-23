#include "CDoAction_Tornado.h"
#include "Global.h"
#include "CAttachment.h"
#include "GameFramework/Character.h"
#include "Components/BoxComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CStatusComponent.h"
#include "Characters/CEnemy.h"
#include "Particles/ParticleSystemComponent.h"


void ACDoAction_Tornado::BeginPlay()
{
	Super::BeginPlay();

	//Attachment::Box -> ¸â¹ö Box
	for (AActor* actor : OwnerCharacter->Children)
	{
		if (actor->IsA<ACAttachment>() && actor->GetActorLabel().Contains("Tornado"))
		{
			Box = CHelpers::GetComponent<UBoxComponent>(actor);
			break;
		}
	}
}

void ACDoAction_Tornado::DoAction()
{
	CheckFalse(State->IsIdleMode());
	CheckTrue(bOnce);

	bOnce = true;
	State->SetActionMode();

	OwnerCharacter->PlayAnimMontage(Datas[0].AnimMontage, Datas[0].PlayRate, Datas[0].StartSection);
	Datas[0].bCanMove ? Status->SetMove() : Status->SetStop();
}

void ACDoAction_Tornado::Begin_DoAction()
{
	Attached = UGameplayStatics::SpawnEmitterAttached(Datas[0].Effect, Box, "");
	Attached->SetRelativeLocation(Datas[0].EffectTransform.GetLocation());
	Attached->SetRelativeScale3D(Datas[0].EffectTransform.GetScale3D());

	ACAttachment* attachment = Cast<ACAttachment>(Box->GetOwner());
	attachment->OnCollision();

	UKismetSystemLibrary::K2_SetTimer(this, "Hitted", HittedTime, true);
}

void ACDoAction_Tornado::End_DoAction()
{
	Status->SetMove();
	State->SetIdleMode();

	FTimerDynamicDelegate timer;
	timer.BindUFunction(this, "Finish");
	UKismetSystemLibrary::K2_SetTimerDelegate(timer, DestroyTime, false);
	
}

void ACDoAction_Tornado::Abort()
{
	Finish();
}

void ACDoAction_Tornado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector location = OwnerCharacter->GetActorLocation();

	Angle += Speed * DeltaTime;

	if (FMath::IsNearlyEqual(Angle, 360.0f))
		Angle = 0.0f;

	FVector rotVector = FVector(Distance, 0, 0);
	FVector yawVector = rotVector.RotateAngleAxis(Angle, FVector::UpVector);
	
	location += yawVector;

	Box->SetWorldLocation(location);
}

void ACDoAction_Tornado::Hitted()
{
	FDamageEvent e;
	for (ACharacter* character : HittedCharacters)
	{
		bool bDead = false;
		ACEnemy* enemy = Cast<ACEnemy>(character);

		if (!!enemy)
		{
			UCStateComponent* state = CHelpers::GetComponent<UCStateComponent>(enemy);
			bDead =  state->IsDeadMode();
		}

		if (!!character && bDead == false)
		{
			character->TakeDamage(Datas[0].Power, e, OwnerCharacter->GetController(), this);
			break;
		}
	}
}

void ACDoAction_Tornado::Finish()
{
	if (!!Attached)
		Attached->DestroyComponent();

	bOnce = false;

	ACAttachment* attachment = Cast<ACAttachment>(Box->GetOwner());
	attachment->OffCollision();

	UKismetSystemLibrary::K2_ClearTimer(this, "Hitted");
}

void ACDoAction_Tornado::OnAttachmentBeginOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter)
{
	HittedCharacters.AddUnique(InOtherCharacter);
}

void ACDoAction_Tornado::OnAttachmentEndOverlap(ACharacter* InAttacker, AActor* InAttackCauser, ACharacter* InOtherCharacter)
{
	HittedCharacters.Remove(InOtherCharacter);
}
