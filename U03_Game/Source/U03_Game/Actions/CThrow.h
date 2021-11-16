#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CThrow.generated.h"

UCLASS()
class U03_GAME_API ACThrow : public AActor
{
	GENERATED_BODY()

private:
	UPROPERTY(EditDefaultsOnly)
		class UParticleSystem* Explosion;

	UPROPERTY(EditDefaultsOnly)
		FTransform ExplosionTransform;

	UPROPERTY(EditDefaultsOnly)
		class USphereComponent* Sphere;

	UPROPERTY(EditDefaultsOnly)
		class UParticleSystemComponent* Particle;

	UPROPERTY(EditDefaultsOnly)
		class UProjectileMovementComponent* Projectile;
	
public:	
	ACThrow();

protected:
	virtual void BeginPlay() override;


};
