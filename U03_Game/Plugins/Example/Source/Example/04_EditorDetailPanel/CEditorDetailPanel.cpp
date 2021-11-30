#include "CEditorDetailPanel.h"
#include "DetailLayoutBuilder.h"
#include "DetailCategoryBuilder.h"
#include "DetailWidgetRow.h"
#include "Widgets/Input/SButton.h"
#include "Objects/CButtonActor.h"

CEditorDetailPanel::CEditorDetailPanel()
{
}

CEditorDetailPanel::~CEditorDetailPanel()
{
}



TSharedRef<IDetailCustomization> CEditorDetailPanel::MakeInstance()
{
    return MakeShareable(new CEditorDetailPanel());
}

void CEditorDetailPanel::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
    IDetailCategoryBuilder& category = DetailBuilder.EditCategory("Change Color");

    category.AddCustomRow(FText::FromString("Color"))
        .ValueContent() //�������гο��� R-Value �ڸ���
        .VAlign(VAlign_Center) //����
        .MaxDesiredWidth(250) //�������� �г�
        [
            SNew(SButton).VAlign(VAlign_Center) //���ο� ��ư ����
            .OnClicked(this, &CEditorDetailPanel::OnClicked)
            .Content()
            [
                SNew(STextBlock).Text(FText::FromString("RandomColor"))
            ]

        ];

    DetailBuilder.GetObjectsBeingCustomized(Objects);
}

FReply CEditorDetailPanel::OnClicked()
{
    for (TWeakObjectPtr<UObject>& object : Objects)
    {
        GLog->Log(object->GetName());
        ACButtonActor* actor = Cast<ACButtonActor>(object);

        if (!!actor)
            actor->ApplyColor(FLinearColor::MakeRandomColor());
    }

    return FReply::Handled();
}