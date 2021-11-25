#include "CCameraSpline.h"
#include "Global.h"
#include "Components/SplineComponent.h"

ACCameraSpline::ACCameraSpline()
{
	CHelpers::CreateComponent(this, &Spline, "Spline");
	CHelpers::GetAsset<UCurveFloat>(&Curve, "CurveFloat'/Game/Curve/Curve_UnNorm.Curve_UnNorm'");

}

void ACCameraSpline::BeginPlay()
{
	Super::BeginPlay();
	
}

