#include "CSliceMesh.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"
#include "Materials/MaterialInstanceConstant.h"


ACSliceMesh::ACSliceMesh()
{
	CHelpers::CreateComponent(this, &Scene, "Scene");
	CHelpers::CreateComponent(this, &StaticMesh, "StaticMesh", Scene);
	CHelpers::CreateComponent(this, &ProcMesh, "ProcMesh", Scene);

	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/StaticMeshes/Cube.Cube'");
	StaticMesh->SetStaticMesh(mesh);

	UMaterialInstanceConstant* material;
	CHelpers::GetAsset<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/Materials/MAT_Base_Inst.MAT_Base_Inst'");
	StaticMesh->SetMaterial(0, material);

	StaticMesh->SetVisibility(false);
	StaticMesh->SetCollisionProfileName("NoCollision");

	ProcMesh->SetSimulatePhysics(true);
	ProcMesh->bUseComplexAsSimpleCollision = false;

}

void ACSliceMesh::OnConstruction(const FTransform& Transform)
{
	UKismetProceduralMeshLibrary::CopyProceduralMeshFromStaticMeshComponent
	(
		StaticMesh, 0, ProcMesh, false
	);
}

void ACSliceMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

