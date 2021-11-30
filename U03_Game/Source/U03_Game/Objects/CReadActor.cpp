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
	//Min~Max LOD 설정..인데 원본 메쉬의 Max를 그대로 유지
	Mesh->SetLODDataCount(1, Mesh->LODData.Num());

	//메쉬컴포 -> 메쉬에셋 읽어오기
	UStaticMesh* mesh = Mesh->GetStaticMesh();

	//메쉬컴포에서 LOD 정보 읽어오기
	FStaticMeshComponentLODInfo* lodInfo = &Mesh->LODData[0];

	//기존의 정점 컬러 날리고 -> 정점 컬러 버퍼를 다시 생성
	lodInfo->PaintedVertices.Empty();
	lodInfo->OverrideVertexColors = new FColorVertexBuffer();

	//원본 메쉬의 서브리소스(정점의 개수, 토폴로지, 정점에...uv 등등) 얻어오기
	FStaticMeshLODResources* resource = &mesh->RenderData->LODResources[0];

	//원본 메시의 정점 개수만큼 풀링(배열화)
	TArray<FColor> colors;
	colors.Reserve(resource->GetNumVertices() - 1); //FColor colors[resource->GetNumVertices() - 1]

	//랜덤컬러 서브리소스 생성
	for (int32 i = 0; i < resource->GetNumVertices(); i++)
		colors.Add(FColor::MakeRandomColor());


	//랜덤컬러를 다시 원본 리소스에 넣어주기
	lodInfo->OverrideVertexColors->InitFromColorArray(colors);

	BeginInitResource(lodInfo->OverrideVertexColors); //IASet -> Update
	Mesh->MarkRenderStateDirty(); //DrawCall
}

