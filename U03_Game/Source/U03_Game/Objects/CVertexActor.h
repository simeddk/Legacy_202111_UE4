#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CVertexActor.generated.h"

UCLASS()
class U03_GAME_API ACVertexActor : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(VisibleDefaultsOnly)
		class UProceduralMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
		float Speed = 5.0f;
	
public:	
	ACVertexActor();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	void AddRectangle(int32 InStart);

private:
	TArray<FVector> Vertices;
	TArray<int32> Indices;
};
