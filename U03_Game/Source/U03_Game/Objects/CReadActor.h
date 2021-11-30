#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CReadActor.generated.h"

UCLASS()
class U03_GAME_API ACReadActor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UStaticMeshComponent* Mesh;
	
public:	
	ACReadActor();

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		void PaintVertices();
};
