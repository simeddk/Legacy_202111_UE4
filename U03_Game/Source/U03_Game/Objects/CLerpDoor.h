#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CLerpDoor.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FLerpDoorOpen, class ACPlayer*);
DECLARE_MULTICAST_DELEGATE(FLerpDoorClose);

UCLASS()
class U03_GAME_API ACLerpDoor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere)
		float Speed = 0.02f;

	UPROPERTY(EditAnywhere)
		float MaxDegree = 90.0f;

	UPROPERTY(EditAnywhere)
		bool bHiddenInGame = true;


private:
	UPROPERTY(VisibleDefaultsOnly)
		class USceneComponent* Scene;

	UPROPERTY(VisibleDefaultsOnly)
		class UBoxComponent* Box;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* DoorFrame;

	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Door;

public:
	FLerpDoorOpen OnLerpDoorOpen;
	FLerpDoorClose OnLerpDoorClose;

private:
	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void Open(class ACPlayer* InPlayer);

	UFUNCTION()
		void Close();

	
public:	
	ACLerpDoor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;


private:
	bool bOpen = false;
	float Rotation;
};
