#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CDataAsset.generated.h"

UCLASS()
class EXAMPLE_API UCDataAsset : public UObject
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
		FName Name;

	UPROPERTY(EditAnywhere)
		float Value;

public:
	FORCEINLINE FName GetName() { return Name; }
	FORCEINLINE float GetValue() { return Value; }
	
};
