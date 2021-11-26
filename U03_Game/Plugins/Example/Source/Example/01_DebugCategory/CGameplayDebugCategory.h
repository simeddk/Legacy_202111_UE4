#pragma once

#include "CoreMinimal.h"
#include "GameplayDebuggerCategory.h"
#include "DebugRenderSceneProxy.h"

class EXAMPLE_API CGameplayDebugCategory : public FGameplayDebuggerCategory
{
public:
	CGameplayDebugCategory();
	~CGameplayDebugCategory();

public:
	static TSharedRef<FGameplayDebuggerCategory> MakeInstance();
	

};
