#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"

class EXAMPLE_API CToolbarCommand : public TCommands<CToolbarCommand>
{
public:
	CToolbarCommand();
	~CToolbarCommand();

public:
	//툴바에 "어떤 기능(버튼)"의 UI를 추가할지 정의하는 함수
	virtual void RegisterCommands() override;

public:
	TSharedPtr<FUICommandInfo> Button;
	
};







