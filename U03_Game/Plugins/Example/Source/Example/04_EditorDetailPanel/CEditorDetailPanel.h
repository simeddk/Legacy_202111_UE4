#pragma once

#include "CoreMinimal.h"
#include "IDetailCustomization.h"

class EXAMPLE_API CEditorDetailPanel : public IDetailCustomization
{
public:
	CEditorDetailPanel();
	~CEditorDetailPanel();

public:
	FReply OnClicked();

public:
	static TSharedRef<IDetailCustomization> MakeInstance();
	virtual void CustomizeDetails(IDetailLayoutBuilder& DetailBuilder) override;

private:
	TArray<TWeakObjectPtr<UObject>> Objects;
};
