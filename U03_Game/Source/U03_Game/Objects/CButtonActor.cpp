#include "CButtonActor.h"
#include "Global.h"
#include "Components/StaticMeshComponent.h"
#include "Materials/MaterialInstanceConstant.h"

ACButtonActor::ACButtonActor()
{
	CHelpers::CreateComponent(this, &Mesh, "Mesh");
	
	UStaticMesh* mesh;
	CHelpers::GetAsset<UStaticMesh>(&mesh, "StaticMesh'/Game/StaticMeshes/Cube.Cube'");
	Mesh->SetStaticMesh(mesh);

	UMaterialInstanceConstant* material;
	CHelpers::GetAsset<UMaterialInstanceConstant>(&material, "MaterialInstanceConstant'/Game/Materials/MAT_Base_Inst.MAT_Base_Inst'");

	Mesh->SetMaterial(0, material);
}

void ACButtonActor::ApplyColor(FLinearColor InColor)
{
	CLog::Print("Call!!!");
	UMaterialInstanceConstant* material = Cast<UMaterialInstanceConstant>(Mesh->GetMaterial(0));

	for (FVectorParameterValue& value : material->VectorParameterValues)
	{
		if(value.ParameterInfo.Name.Compare("Color") == 0)
			material->SetVectorParameterValueEditorOnly(value.ParameterInfo.Name, InColor);
	}

}

void ACButtonActor::BeginPlay()
{
	Super::BeginPlay();
	
}


