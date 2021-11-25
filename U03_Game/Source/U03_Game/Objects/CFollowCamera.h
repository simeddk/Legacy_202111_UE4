#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "CFollowCamera.generated.h"

UCLASS()
class U03_GAME_API ACFollowCamera : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UCameraComponent* Camera;
	
public:	
	ACFollowCamera();

	UFUNCTION(BlueprintCallable)
		void SetTimeline();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	UFUNCTION()
		void OnProgress(float Output);

	UFUNCTION(BlueprintCallable)
		void OnFinishProgress();

private:
	

	FTimeline Timeline;
	class ACCameraSpline* Spline;
};
