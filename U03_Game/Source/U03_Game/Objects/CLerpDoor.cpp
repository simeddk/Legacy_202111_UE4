#include "CLerpDoor.h"
#include "Global.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Characters/CPlayer.h"


ACLerpDoor::ACLerpDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent(this, &Scene, "Scene");
	CHelpers::CreateComponent(this, &Box, "Box", Scene);
	CHelpers::CreateComponent(this, &DoorFrame, "DoorFrame", Scene);
	CHelpers::CreateComponent(this, &Door, "Door", DoorFrame);

	UStaticMesh* doorFrameMesh;
	CHelpers::GetAsset<UStaticMesh>(&doorFrameMesh, "StaticMesh'/Game/DoorMesh/Props/SM_DoorFrame.SM_DoorFrame'");
	DoorFrame->SetStaticMesh(doorFrameMesh);

	UStaticMesh* doorMesh;
	CHelpers::GetAsset<UStaticMesh>(&doorMesh, "StaticMesh'/Game/DoorMesh/Props/SM_Door.SM_Door'");
	Door->SetStaticMesh(doorMesh);
	Door->SetRelativeLocation(FVector(0, 45, 0));

	Box->InitBoxExtent(FVector(150, 50, 100));
	Box->SetRelativeLocation(FVector(0, 0, 100));
	Box->SetCollisionProfileName("Trigger");
}

void ACLerpDoor::BeginPlay()
{
	Super::BeginPlay();

	Box->SetHiddenInGame(bHiddenInGame);

	Box->OnComponentBeginOverlap.AddDynamic(this, &ACLerpDoor::OnBeginOverlap);
	Box->OnComponentEndOverlap.AddDynamic(this, &ACLerpDoor::OnEndOverlap);

	OnLerpDoorOpen.AddUFunction(this, "Open");
	OnLerpDoorClose.AddUFunction(this, "Close");
	
}

void ACLerpDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rotation = Door->GetRelativeRotation();

	if (bOpen)
		Door->SetRelativeRotation(FMath::Lerp(rotation, FRotator(0, Rotation, 0), Speed));
	else
		Door->SetRelativeRotation(FMath::Lerp(rotation, FRotator(0, 0, 0), Speed));
}

void ACLerpDoor::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckNull(OtherActor);
	CheckNull(OtherComp);
	CheckTrue(OtherActor == this);
	CheckFalse(OtherActor->GetClass()->IsChildOf(ACPlayer::StaticClass()));
	
	if (OnLerpDoorOpen.IsBound())
		OnLerpDoorOpen.Broadcast(Cast<ACPlayer>(OtherActor));
}

void ACLerpDoor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckNull(OtherActor);
	CheckNull(OtherComp);
	CheckTrue(OtherActor == this);
	CheckFalse(OtherActor->GetClass()->IsChildOf(ACPlayer::StaticClass()));

	if (OnLerpDoorClose.IsBound())
		OnLerpDoorClose.Broadcast();
}

void ACLerpDoor::Open(ACPlayer* InPlayer)
{
	FVector forward = GetActorForwardVector();
	FVector playerForward = InPlayer->GetActorForwardVector();
	
	float direction = FMath::Sign(forward | playerForward);
	Rotation = direction * MaxDegree;

	bOpen = true;
}

void ACLerpDoor::Close()
{
	bOpen = false;
}
