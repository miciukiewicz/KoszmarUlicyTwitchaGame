#include "EndgameDoorActor.h"
#include "Kismet\GameplayStatics.h"
#include "Components\AudioComponent.h"

AEndgameDoorActor::AEndgameDoorActor()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(RootComponent);

	SoundCue = CreateDefaultSubobject<UAudioComponent>(TEXT("DoorSound"));
	SoundCue->SetupAttachment(DoorMesh);
	SoundCue->SetRelativeLocation(FVector(45.f, 0.f, 90.f));
	SoundCue->bAutoActivate = false;
}

void AEndgameDoorActor::OnInteract()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("END GAME"));

	if (SoundCue != nullptr)
		SoundCue->Play();

	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

void AEndgameDoorActor::BeginPlay()
{
	Super::BeginPlay();
}

void AEndgameDoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}