#include "GhostActor.h"
#include "Components\AudioComponent.h"
#include "Kismet\GameplayStatics.h"
#include "Kismet\KismetMathLibrary.h"

AGhostActor::AGhostActor()
{
	PrimaryActorTick.bCanEverTick = true;

	GhostMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	GhostMesh->SetupAttachment(RootComponent);

	GhostSoundCue = CreateDefaultSubobject<UAudioComponent>(TEXT("GhostSound"));
	GhostSoundCue->SetupAttachment(GhostMesh);
}

void AGhostActor::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	Direction = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - StartLocation;

	TotalDistance = Direction.Size();

	Direction = Direction.GetSafeNormal();
}

void AGhostActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator PlayerRot = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation());
	SetActorRotation(PlayerRot);

	FVector Location = GetActorLocation();

	Location += GetActorForwardVector() * (GhostSpeed * DeltaTime);

	SetActorLocation(Location);
}