#include "CGameplayDebugCategory.h"

CGameplayDebugCategory::CGameplayDebugCategory()
{
	UE_LOG(LogTemp, Error, L"CGameplayDebugCategory Start");
}

CGameplayDebugCategory::~CGameplayDebugCategory()
{
	UE_LOG(LogTemp, Error, L"CGameplayDebugCategory End");
}

TSharedRef<FGameplayDebuggerCategory> CGameplayDebugCategory::MakeInstance()
{
	return MakeShareable(new FGameplayDebuggerCategory());
}