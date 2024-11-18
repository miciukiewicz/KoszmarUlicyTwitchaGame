#include "EndgameDoorActor.h"
#include "PlayerCharacter.h"
#include "Components\BoxComponent.h"
#include "Kismet\GameplayStatics.h"
#include "Components\AudioComponent.h"

AEndgameDoorActor::AEndgameDoorActor()
{
	PrimaryActorTick.bCanEverTick = true;

	EndgameDoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	EndgameDoorMesh->SetupAttachment(RootComponent);

	DoorSoundCue = CreateDefaultSubobject<UAudioComponent>(TEXT("DoorSound"));
	DoorSoundCue->SetupAttachment(EndgameDoorMesh);
	DoorSoundCue->SetRelativeLocation(FVector(45.f, 0.f, 90.f));
	DoorSoundCue->bAutoActivate = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(EndgameDoorMesh);
}

void AEndgameDoorActor::OnInteract()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("END GAME"));

	if (DoorSoundCue != nullptr)
		DoorSoundCue->Play();
}

void AEndgameDoorActor::BeginPlay()
{
	Super::BeginPlay();
}

void AEndgameDoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}