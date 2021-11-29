#include "CPlayer.h"
#include "Global.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/PostProcessComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CStatusComponent.h"
#include "Components/COptionComponent.h"
#include "Components/CStateComponent.h"
#include "Components/CMontagesComponent.h"
#include "Components/CActionComponent.h"
#include "Components/CFeetComponent.h"
#include "Materials/MaterialInstanceConstant.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Widgets/CUserWidget_Select.h"
#include "Widgets/CUserWidget_SelectItem.h"
#include "Objects/CInteractDoor.h"
#include "03_CutomDataAsset/CDataAsset.h"

ACPlayer::ACPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	//Create SceneComponent
	CHelpers::CreateComponent(this, &SpringArm, "SpringArm", GetMesh());
	CHelpers::CreateComponent(this, &Camera, "Camera", SpringArm);
	CHelpers::CreateComponent(this, &PostProcess, "PostProcess", GetRootComponent());

	//Create ActorComponent
	CHelpers::CreateActorComponent(this, &Action, "Action");
	CHelpers::CreateActorComponent(this, &Montages, "Montages");
	CHelpers::CreateActorComponent(this, &Status, "Status");
	CHelpers::CreateActorComponent(this, &Option, "Option");
	CHelpers::CreateActorComponent(this, &State, "State");
	CHelpers::CreateActorComponent(this, &Feet, "Feet");

	//Component Settings
	GetMesh()->SetRelativeLocation(FVector(0, 0, -88));
	GetMesh()->SetRelativeRotation(FRotator(0, -90, 0));

	USkeletalMesh* mesh;
	CHelpers::GetAsset<USkeletalMesh>(&mesh, "SkeletalMesh'/Game/Character/Mesh/SK_Mannequin.SK_Mannequin'");
	GetMesh()->SetSkeletalMesh(mesh);

	TSubclassOf<UAnimInstance> animInstance;
	CHelpers::GetClass<UAnimInstance>(&animInstance, "AnimBlueprint'/Game/Player/ABP_CPlayer.ABP_CPlayer_C'");
	GetMesh()->SetAnimInstanceClass(animInstance);

	SpringArm->SetRelativeLocation(FVector(0, 0, 140));
	SpringArm->SetRelativeRotation(FRotator(0, 90, 0));
	SpringArm->TargetArmLength = 200.0f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->bUsePawnControlRotation = true;

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->MaxWalkSpeed = Status->GetSprintSpeed();
	GetCharacterMovement()->RotationRate = FRotator(0, 720, 0);
	GetCharacterMovement()->bOrientRotationToMovement = true;

	UTexture* dirtMask;
	CHelpers::GetAsset<UTexture>(&dirtMask, "Texture2D'/Game/Textures/Baisic/T_SpeedLine.T_SpeedLine'");
	PostProcess->bEnabled = true;
	PostProcess->Settings.BloomDirtMask = dirtMask;
	PostProcess->Settings.bOverride_BloomDirtMask = false;
	PostProcess->Settings.bOverride_BloomDirtMaskIntensity = false;
	PostProcess->Settings.BloomDirtMaskIntensity = 25.0f;

	//Widget
	CHelpers::GetClass<UCUserWidget_Select>(&SelectWidgetClass, "WidgetBlueprint'/Game/Widgets/WB_Select.WB_Select_C'");

	//Custom DA Test
	CHelpers::GetAsset<UCDataAsset>(&Test_DataAsset, "CDataAsset'/Game/Objects/DA_Test1.DA_Test1'");
}


void ACPlayer::BeginPlay()
{
	Super::BeginPlay();

	UMaterialInstanceConstant* body, *logo;
	//CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&body, "MaterialInstanceConstant'/Game/Materials/M_UE4Man_Body_Inst.M_UE4Man_Body_Inst'");
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&body, "MaterialInstanceConstant'/Game/Materials/MAT_Smear_Inst.MAT_Smear_Inst'");
	CHelpers::GetAssetDynamic<UMaterialInstanceConstant>(&logo, "MaterialInstanceConstant'/Game/Materials/M_UE4Man_ChestLogo_Inst.M_UE4Man_ChestLogo_Inst'");

	BodyMaterial = UMaterialInstanceDynamic::Create(body, this);
	LogoMaterial = UMaterialInstanceDynamic::Create(logo, this);
	

	GetMesh()->SetMaterial(0, BodyMaterial);
	GetMesh()->SetMaterial(1, LogoMaterial);

	State->OnStateTypeChanged.AddDynamic(this, &ACPlayer::OnStateTypeChanged);

	Action->SetUnarmedMode();

	SelectWidget = CreateWidget<UCUserWidget_Select, APlayerController>(GetController<APlayerController>(), SelectWidgetClass);
	SelectWidget->AddToViewport();
	SelectWidget->SetVisibility(ESlateVisibility::Hidden);

	SelectWidget->GetItem("Item1")->OnUserWidget_Select_Clicked.AddDynamic(this, &ACPlayer::OnFist);
	SelectWidget->GetItem("Item2")->OnUserWidget_Select_Clicked.AddDynamic(this, &ACPlayer::OnOneHand);
	SelectWidget->GetItem("Item3")->OnUserWidget_Select_Clicked.AddDynamic(this, &ACPlayer::OnTwoHand);
	SelectWidget->GetItem("Item4")->OnUserWidget_Select_Clicked.AddDynamic(this, &ACPlayer::OnMagicBall);
	SelectWidget->GetItem("Item5")->OnUserWidget_Select_Clicked.AddDynamic(this, &ACPlayer::OnWarp);
	SelectWidget->GetItem("Item6")->OnUserWidget_Select_Clicked.AddDynamic(this, &ACPlayer::OnTornado);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &ACPlayer::OnBeginOverlap);
	GetCapsuleComponent()->OnComponentEndOverlap.AddDynamic(this, &ACPlayer::OnEndOverlap);

	//Test Custom DataAsset
	if (!!Test_DataAsset)
	{
		CLog::Print(Test_DataAsset->GetName().ToString());
		CLog::Print(Test_DataAsset->GetValue());
	}
}

void ACPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ACPlayer::OnMoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACPlayer::OnMoveRight);
	PlayerInputComponent->BindAxis("HorizontalLook", this, &ACPlayer::OnHorizontalLook);
	PlayerInputComponent->BindAxis("VerticalLook", this, &ACPlayer::OnVerticalLook);
	PlayerInputComponent->BindAxis("Zoom", this, &ACPlayer::OnZoom);

	PlayerInputComponent->BindAction("Walk", EInputEvent::IE_Pressed, this, &ACPlayer::OnWalk);
	PlayerInputComponent->BindAction("Walk", EInputEvent::IE_Released, this, &ACPlayer::OffWalk);

	PlayerInputComponent->BindAction("Evade", EInputEvent::IE_Pressed, this, &ACPlayer::OnEvade);

	PlayerInputComponent->BindAction("Fist", EInputEvent::IE_Pressed, this, &ACPlayer::OnFist);
	PlayerInputComponent->BindAction("OneHand", EInputEvent::IE_Pressed, this, &ACPlayer::OnOneHand);
	PlayerInputComponent->BindAction("TwoHand", EInputEvent::IE_Pressed, this, &ACPlayer::OnTwoHand);
	PlayerInputComponent->BindAction("MagicBall", EInputEvent::IE_Pressed, this, &ACPlayer::OnMagicBall);
	PlayerInputComponent->BindAction("Warp", EInputEvent::IE_Pressed, this, &ACPlayer::OnWarp);
	PlayerInputComponent->BindAction("Tornado", EInputEvent::IE_Pressed, this, &ACPlayer::OnTornado);

	PlayerInputComponent->BindAction("Action", EInputEvent::IE_Pressed, this, &ACPlayer::OnDoAction);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &ACPlayer::OnAim);
	PlayerInputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &ACPlayer::OffAim);

	PlayerInputComponent->BindAction("SelectAction", EInputEvent::IE_Pressed, this, &ACPlayer::OnSelectAction);
	PlayerInputComponent->BindAction("SelectAction", EInputEvent::IE_Released, this, &ACPlayer::OffSelectAction);

	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &ACPlayer::OnInteract);
}

FGenericTeamId ACPlayer::GetGenericTeamId() const
{
	return FGenericTeamId(TeamID);
}

void ACPlayer::OnMoveForward(float InAxis)
{
	CheckFalse(Status->CanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetForwardVector();

	AddMovementInput(direction, InAxis);
	UpdateSmear();
}

void ACPlayer::OnMoveRight(float InAxis)
{
	CheckFalse(Status->CanMove());

	FRotator rotator = FRotator(0, GetControlRotation().Yaw, 0);
	FVector direction = FQuat(rotator).GetRightVector();

	AddMovementInput(direction, InAxis);
	UpdateSmear();
}

void ACPlayer::OnHorizontalLook(float InAxis)
{
	float rate = Option->GetHorizontalLookRate();
	AddControllerYawInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnVerticalLook(float InAxis)
{
	float rate = Option->GetVerticalLookRate();
	AddControllerPitchInput(InAxis * rate * GetWorld()->GetDeltaSeconds());
}

void ACPlayer::OnZoom(float InAxis)
{
	SpringArm->TargetArmLength -= (InAxis * Option->GetZoomSpeed() * GetWorld()->GetDeltaSeconds());
	SpringArm->TargetArmLength = FMath::Clamp(SpringArm->TargetArmLength, Option->GetMinZoomRange(), Option->GetMaxZoomRange());
}

void ACPlayer::OnWalk()
{
	GetCharacterMovement()->MaxWalkSpeed = Status->GetRunSpeed();
}

void ACPlayer::OffWalk()
{
	GetCharacterMovement()->MaxWalkSpeed = Status->GetSprintSpeed();
}

void ACPlayer::OnEvade()
{
	CheckFalse(State->IsIdleMode());
	CheckFalse(Status->CanMove());

	if (Action->IsUnarmedMode())
	{
		GetCharacterMovement()->GravityScale = 0.0f;

		FVector direction = FVector::ZeroVector;
		if (FMath::IsNearlyZero(GetVelocity().Size()))
			direction = GetActorUpVector();
		else
			direction = GetVelocity().GetSafeNormal();

		FVector launch = direction * GetCharacterMovement()->MaxWalkSpeed * 0.5f;

		LaunchCharacter(launch, false, true);
		SpringArm->TargetArmLength = 300.0f;
		UKismetSystemLibrary::K2_SetTimer(this, "EndEvade", 1.0f, false);
		return;
	}


	if (InputComponent->GetAxisValue("MoveForward") < 0.0f)
	{
		State->SetBackStepMode();
		return;
	}

	State->SetRollMode();
}

void ACPlayer::EndEvade()
{
	GetCharacterMovement()->GravityScale = 1.0f;
	SpringArm->TargetArmLength = 200.0f;
}

void ACPlayer::Begin_BackStep()
{
	bUseControllerRotationYaw = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

	Montages->PlayBackStep();
}

void ACPlayer::Begin_Roll()
{
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	
	FVector start = GetActorLocation();
	FVector target = start + GetVelocity().GetSafeNormal2D();

	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(start, target));

	Montages->PlayRoll();
}

void ACPlayer::End_BackStep()
{
	if (Action->IsUnarmedMode())
	{
		bUseControllerRotationYaw = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}

	State->SetIdleMode();
}

void ACPlayer::End_Roll()
{
	if (Action->IsUnarmedMode() == false)
	{
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}


	State->SetIdleMode();
}

void ACPlayer::UpdateSmear()
{
	if (FMath::IsNearlyEqual(GetCharacterMovement()->MaxWalkSpeed, Status->GetSprintSpeed()))
	{
		BodyMaterial->SetVectorParameterValue("Direction", -GetVelocity());
		BodyMaterial->SetScalarParameterValue("Amount", GetCharacterMovement()->MaxWalkSpeed * SmearLength);
		return;
	}

	BodyMaterial->SetVectorParameterValue("Direction", FVector::ZeroVector);
	BodyMaterial->SetScalarParameterValue("Amount", 0.0f);
}

void ACPlayer::OnFist()
{
	CheckFalse(State->IsIdleMode());

	Action->SetFistMode();
}

void ACPlayer::OnOneHand()
{
	CheckFalse(State->IsIdleMode());

	Action->SetOneHandMode();
}

void ACPlayer::OnTwoHand()
{
	CheckFalse(State->IsIdleMode());

	Action->SetTwoHandMode();
}

void ACPlayer::OnMagicBall()
{
	CheckFalse(State->IsIdleMode());

	Action->SetMagicBallMode();
}

void ACPlayer::OnWarp()
{
	CheckFalse(State->IsIdleMode());

	Action->SetWarpMode();
}

void ACPlayer::OnTornado()
{
	CheckFalse(State->IsIdleMode());

	Action->SetTornadoMode();
}

void ACPlayer::OnDoAction()
{
	Action->DoAction();
}

void ACPlayer::OnAim()
{
	Action->DoOnAim();
}

void ACPlayer::OffAim()
{
	Action->DoOffAim();
}

void ACPlayer::OnSelectAction()
{
	CheckFalse(State->IsIdleMode());

	SelectWidget->SetVisibility(ESlateVisibility::Visible);
	GetController<APlayerController>()->bShowMouseCursor = true;

	GetController<APlayerController>()->SetInputMode(FInputModeGameAndUI());

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.1f);

}

void ACPlayer::OffSelectAction()
{
	PrintLine();
	SelectWidget->SetVisibility(ESlateVisibility::Hidden);
	GetController<APlayerController>()->bShowMouseCursor = false;

	GetController<APlayerController>()->SetInputMode(FInputModeGameOnly());

	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
}

void ACPlayer::OnInteract()
{
	if (!!InteractDoor)
		InteractDoor->Interact(Camera->GetForwardVector());
}

float ACPlayer::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	DamageInstigator = EventInstigator;

	Action->AbortByDamaged();

	Status->SubHealth(damage);

	if (Status->GetHealth() <= 0.0f)
	{
		State->SetDeadMode();
		return 0.0f;
	}

	State->SetHittedMode();

	return Status->GetHealth();
}


void ACPlayer::Hitted()
{
	PostProcess->Settings.bOverride_BloomDirtMask = true;
	PostProcess->Settings.bOverride_BloomDirtMaskIntensity = true;
	UKismetSystemLibrary::K2_SetTimer(this, "Hitted_End", 0.2f, false);

	Montages->PlayHitted();
	Status->SetMove();
}

void ACPlayer::Hitted_End()
{
	PostProcess->Settings.bOverride_BloomDirtMask = false;
	PostProcess->Settings.bOverride_BloomDirtMaskIntensity = false;
}

void ACPlayer::Dead()
{
	Action->Dead();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Montages->PlayDead();
}

void ACPlayer::End_Dead()
{
	Action->End_Dead();

	UKismetSystemLibrary::QuitGame(GetWorld(), GetController<APlayerController>(), EQuitPreference::Quit, false);
}



void ACPlayer::OnStateTypeChanged(EStateType InPrevType, EStateType InNewType)
{
	switch (InNewType)
	{
		case EStateType::Roll:		Begin_Roll(); break;
		case EStateType::BackStep:	Begin_BackStep(); break;
		case EStateType::Hitted:	Hitted(); break;
		case EStateType::Dead:		Dead(); break;
	}
}

void ACPlayer::ChangeColor(FLinearColor InColor)
{
	BodyMaterial->SetVectorParameterValue("BodyColor", InColor);
	LogoMaterial->SetVectorParameterValue("BodyColor", InColor);
}

void ACPlayer::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckNull(OtherActor);
	CheckNull(OtherComp);
	CheckTrue(OtherActor == this);

	//Cast<ACInteractDoor>(OtherActor)
	//OtherActor->IsA<ACInteractDoor>
	if (OtherActor->GetClass()->IsChildOf(ACInteractDoor::StaticClass()))
		InteractDoor = Cast<ACInteractDoor>(OtherActor);
}

void ACPlayer::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckNull(OtherActor);
	CheckNull(OtherComp);
	CheckTrue(OtherActor == this);

	//Cast<ACInteractDoor>(OtherActor)
	//OtherActor->IsA<ACInteractDoor>
	if (OtherActor->GetClass()->IsChildOf(ACInteractDoor::StaticClass()))
		InteractDoor = nullptr;
}