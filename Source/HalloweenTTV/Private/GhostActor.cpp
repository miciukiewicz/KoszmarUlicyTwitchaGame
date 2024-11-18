#include "GhostActor.h"
#include "Components\AudioComponent.h"
#include "Kismet\GameplayStatics.h"
#include "Kismet\KismetMathLibrary.h"

AGhostActor::AGhostActor()
{
	PrimaryActorTick.bCanEverTick = true;

	GhostMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("GhostMesh"));
	GhostMesh->SetupAttachment(RootComponent);

	GhostSoundCue = CreateDefaultSubobject<UAudioComponent>(TEXT("GhostSound"));
	GhostSoundCue->SetupAttachment(GhostMesh);
}

void AGhostActor::BeginPlay()
{
	Super::BeginPlay();

	vStartLocation = GetActorLocation();

	vDirection = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - vStartLocation;

	fTotalDistance = vDirection.Size();

	vDirection = vDirection.GetSafeNormal();
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