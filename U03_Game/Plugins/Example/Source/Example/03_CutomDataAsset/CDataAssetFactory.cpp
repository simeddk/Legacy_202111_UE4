#include "CDataAssetFactory.h"
#include "CDataAsset.h"

UCDataAssetFactory::UCDataAssetFactory()
{
	bCreateNew = true; //이게 있어야 NewObject를 사용할 수 있음
	bEditAfterNew = true; //이게 있어야 생성 후에 사용자가 임의로 편집 가능
	SupportedClass = UCDataAsset::StaticClass(); //어떤 클래스를 팩토리로 찍어낼건지
}

UObject* UCDataAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	return NewObject<UCDataAsset>(InParent, InClass, InName, Flags);
}
