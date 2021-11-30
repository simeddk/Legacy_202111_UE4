#include "CFileActor.h"
#include "Global.h"
#include "Serialization/BufferArchive.h"

ACFileActor::ACFileActor()
{
	CHelpers::CreateActorComponent(this, &InputComponent, "InputComponent");
}

void ACFileActor::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* controller = GetWorld()->GetFirstPlayerController();
	EnableInput(controller);
	
	InputComponent->BindAction("FileSave", EInputEvent::IE_Pressed, this, &ACFileActor::OnSave);
	InputComponent->BindAction("FileLoad", EInputEvent::IE_Pressed, this, &ACFileActor::OnLoad);
}

void ACFileActor::OnSave()
{
	FFileData data;
	data.Name = "SOMEDDK";
	data.Health = 777.7f;

	FBufferArchive buffer;
	//buffer << data.Name;
	//buffer << data.Health;
	buffer << data;


	CheckTrue(buffer.Num() < 1);
	buffer.FlushCache();
	FString str = FPaths::ProjectDir() + FString("Test.bin");
	bool b = FFileHelper::SaveArrayToFile(buffer, *str);
	buffer.Empty();
	CLog::Print(b ? "Saved" : "Faild");
}

void ACFileActor::OnLoad()
{
	FString str = FPaths::ProjectDir() + FString("Test.bin");

	FBufferArchive buffer;
	FFileHelper::LoadFileToArray(buffer, *str);

	FMemoryReader reader = FMemoryReader(buffer, true);
	reader.Seek(0);

	FFileData data;
	//reader << data.Name;
	//reader << data.Health;
	reader << data;

	CLog::Print(data.Name.ToString(), -1, 10.0f, FColor::Red);
	CLog::Print(data.Health, -1, 10.0f, FColor::Red);

	reader.FlushCache();
	reader.Close();
}