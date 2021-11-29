#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "AssetTypeCategories.h"

class EXAMPLE_API CDataAssetToolAction : public FAssetTypeActions_Base
{
public:
	CDataAssetToolAction(EAssetTypeCategories::Type InCategory);
	~CDataAssetToolAction();

public:
	virtual FText GetName() const override;
	virtual FColor GetTypeColor() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual uint32 GetCategories() override;

private:
	EAssetTypeCategories::Type Category;
};
