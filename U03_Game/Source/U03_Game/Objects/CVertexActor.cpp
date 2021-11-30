#include "CVertexActor.h"
#include "Global.h"
#include "ProceduralMeshComponent.h"

ACVertexActor::ACVertexActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CHelpers::CreateComponent(this, &Mesh, "Mesh");

	float w = 50, h = 50, d = 50;

	//Front
	Vertices.Add(FVector(-d, -w, -h));//전좌하
	Vertices.Add(FVector(-d, -w, +h));//전좌상
	Vertices.Add(FVector(-d, +w, -h));//전우하
	Vertices.Add(FVector(-d, +w, +h));//전우상
	AddRectangle(0);

	//Back
	Vertices.Add(FVector(+d, -w, -h));//후좌하
	Vertices.Add(FVector(+d, +w, -h));//후우하
	Vertices.Add(FVector(+d, -w, +h));//후좌상
	Vertices.Add(FVector(+d, +w, +h));//후우상
	AddRectangle(4);

	//Top
	Vertices.Add(FVector(-d, -w, +h));//전좌상
	Vertices.Add(FVector(+d, -w, +h));//후좌상
	Vertices.Add(FVector(-d, +w, +h));//전우상
	Vertices.Add(FVector(+d, +w, +h));//후우상
	AddRectangle(8);

	//Bottom
	Vertices.Add(FVector(-d, -w, -h));//전좌하
	Vertices.Add(FVector(-d, +w, -h));//전우하
	Vertices.Add(FVector(+d, -w, -h));//후좌하
	Vertices.Add(FVector(+d, +w, -h));//후우하
	AddRectangle(12);

	//Left
	Vertices.Add(FVector(+d, -w, -h));//후좌하
	Vertices.Add(FVector(+d, -w, +h));//후좌상
	Vertices.Add(FVector(-d, -w, -h));//전좌하
	Vertices.Add(FVector(-d, -w, +h));//전좌상
	AddRectangle(16);

	//Right
	Vertices.Add(FVector(-d, +w, -h));//전우하
	Vertices.Add(FVector(-d, +w, +h));//전우상
	Vertices.Add(FVector(+d, +w, -h));//후우하
	Vertices.Add(FVector(+d, +w, +h));//후우상
	AddRectangle(20);

	//CreateMesh
	Mesh->CreateMeshSection
	(
		0, //Section No
		Vertices, //Vertices
		Indices, //Indices
		TArray<FVector>(), //Normal
		TArray<FVector2D>(), //Uv
		TArray<FColor>(), //Color
		TArray<FProcMeshTangent>(), //Tanget
		true
	);

}

void ACVertexActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACVertexActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int32 i = 0; i < Vertices.Num(); i++)
		Vertices[i] += FVector(0, 0, Speed * DeltaTime);

	Mesh->UpdateMeshSection
	(
		0, //Section No
		Vertices, //Vertices <----- Update
		TArray<FVector>(), //Noraml
		TArray<FVector2D>(), //Uv
		TArray<FColor>(), //Color
		TArray<FProcMeshTangent>() //Tangent
	);
}

void ACVertexActor::AddRectangle(int32 InStart)
{
	//2, 1, 0, 3, 1, 2 -> RH
	Indices.Add(InStart + 2);
	Indices.Add(InStart + 1);
	Indices.Add(InStart + 0);

	Indices.Add(InStart + 3);
	Indices.Add(InStart + 1);
	Indices.Add(InStart + 2);
}

