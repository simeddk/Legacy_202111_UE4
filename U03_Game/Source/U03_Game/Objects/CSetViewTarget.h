#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CSetViewTarget.generated.h"

UCLASS()
class U03_GAME_API ACSetViewTarget : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditInstanceOnly)
		TArray<class ACameraActor*> Cameras;

	UPROPERTY(EditInstanceOnly)
		bool bUseChangeCamera = false;
	
public:	
	ACSetViewTarget();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void Change();

private:
	uint32 Index;


};
