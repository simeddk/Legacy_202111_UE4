#include "CDataAssetToolAction.h"
#include "CDataAsset.h"

CDataAssetToolAction::CDataAssetToolAction(EAssetTypeCategories::Type InCategory)
	: Category(InCategory)
{
}

CDataAssetToolAction::~CDataAssetToolAction()
{
}

FText CDataAssetToolAction::GetName() const
{
	return FText::FromString(L"Awesome Asset");
}

FColor CDataAssetToolAction::GetTypeColor() const
{
	return FColor::Orange;
}

UClass* CDataAssetToolAction::GetSupportedClass() const
{
	return UCDataAsset::StaticClass();
}

uint32 CDataAssetToolAction::GetCategories()
{
	return Category;
}