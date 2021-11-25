#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CCameraSpline.generated.h"

UCLASS()
class U03_GAME_API ACCameraSpline : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(VisibleAnywhere)
		class UCurveFloat* Curve;

	UPROPERTY(VisibleAnywhere)
		class USplineComponent* Spline;

public:	
	ACCameraSpline();

public:
	FORCEINLINE class UCurveFloat* GetCurve() { return Curve; }
	FORCEINLINE class USplineComponent* GetSpline() { return Spline; }

protected:
	virtual void BeginPlay() override;



};
