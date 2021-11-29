#include "CDataAssetFactory.h"
#include "CDataAsset.h"

UCDataAssetFactory::UCDataAssetFactory()
{
	bCreateNew = true; //�̰� �־�� NewObject�� ����� �� ����
	bEditAfterNew = true; //�̰� �־�� ���� �Ŀ� ����ڰ� ���Ƿ� ���� ����
	SupportedClass = UCDataAsset::StaticClass(); //� Ŭ������ ���丮�� ������
}

UObject* UCDataAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	return NewObject<UCDataAsset>(InParent, InClass, InName, Flags);
}
