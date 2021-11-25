#include "CSetViewTarget.h"
#include "Global.h"
#include "Camera/CameraActor.h"

ACSetViewTarget::ACSetViewTarget()
{

}

void ACSetViewTarget::BeginPlay()
{
	Super::BeginPlay();

	UKismetSystemLibrary::K2_SetTimer(this, "Change", 2.0f, true);
	
}

void ACSetViewTarget::Change()
{
	//APlayerCameraManager* cameraManager = UGameplayStatics::GetPlayerCameraManager(GetWorld(), 0);
	//CheckNull(cameraManager);
	//cameraManager->SetViewTarget(Cameras[Index]);
	//Index++;
	//Index %= Cameras.Num();

	CheckFalse(bUseChangeCamera);
	APlayerController* controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	CheckNull(controller);
	CheckTrue(Cameras.Num() < 1);
	controller->SetViewTargetWithBlend(Cameras[Index], 2.0f, EViewTargetBlendFunction::VTBlend_Linear);

	Index++;
	Index %= Cameras.Num();
}

