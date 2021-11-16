#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CHUD.generated.h"

UCLASS()
class U03_GAME_API ACHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	FORCEINLINE void SetDraw() { bDraw = true; }
	FORCEINLINE void SetNoDraw() { bDraw = false; }

public:
	ACHUD();

	virtual void DrawHUD() override;

private:
	UPROPERTY(EditDefaultsOnly)
		class UTexture2D* Texture;


private:
	bool bDraw;

};
