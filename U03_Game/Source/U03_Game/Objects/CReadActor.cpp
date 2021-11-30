#include "CReadActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"

ACReadActor::ACReadActor()
{
	CHelpers::CreateComponent(this, &Mesh, "Mesh");

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/StaticMeshes/Cube.Cube'"); //SM_Cube
	Mesh->SetStaticMesh(mesh);

	UMaterialInstanceConstant* material;
	CHelpers::GetAsset<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/Materials/MAT_VertexColor_Inst.MAT_VertexColor_Inst'"); //MAT_VertexColor
	Mesh->SetMaterial(0, material);
}

void ACReadActor::BeginPlay()
{
	Super::BeginPlay();

	UKismetSystemLibrary::K2_SetTimer(this, "PaintVertices", 1.0f, true);
	
}

void ACReadActor::PaintVertices()
{
	//Min~Max LOD ����..�ε� ���� �޽��� Max�� �״�� ����
	Mesh->SetLODDataCount(1, Mesh->LODData.Num());

	//�޽����� -> �޽����� �о����
	UStaticMesh* mesh = Mesh->GetStaticMesh();

	//�޽��������� LOD ���� �о����
	FStaticMeshComponentLODInfo* lodInfo = &Mesh->LODData[0];

	//������ ���� �÷� ������ -> ���� �÷� ���۸� �ٽ� ����
	lodInfo->PaintedVertices.Empty();
	lodInfo->OverrideVertexColors = new FColorVertexBuffer();

	//���� �޽��� ���긮�ҽ�(������ ����, ��������, ������...uv ���) ������
	FStaticMeshLODResources* resource = &mesh->RenderData->LODResources[0];

	//���� �޽��� ���� ������ŭ Ǯ��(�迭ȭ)
	TArray<FColor> colors;
	colors.Reserve(resource->GetNumVertices() - 1); //FColor colors[resource->GetNumVertices() - 1]

	//�����÷� ���긮�ҽ� ����
	for (int32 i = 0; i < resource->GetNumVertices(); i++)
		colors.Add(FColor::MakeRandomColor());


	//�����÷��� �ٽ� ���� ���ҽ��� �־��ֱ�
	lodInfo->OverrideVertexColors->InitFromColorArray(colors);

	BeginInitResource(lodInfo->OverrideVertexColors); //IASet -> Update
	Mesh->MarkRenderStateDirty(); //DrawCall
}

