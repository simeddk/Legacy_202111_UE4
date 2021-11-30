#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CFileActor.generated.h"

USTRUCT(BlueprintType)
struct FFileData
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
		FName Name;

	UPROPERTY(EditAnywhere)
		float Health;

	friend FArchive& operator<<(FArchive& InArchive, FFileData& InData)
	{
		return InArchive << InData.Name << InData.Health;
	}
};

UCLASS()
class U03_GAME_API ACFileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACFileActor();

protected:
	virtual void BeginPlay() override;


private:
	void OnSave();
	void OnLoad();

};
