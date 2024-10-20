#include "CandyActor.h"
#include "MyGameInstance.h"
#include "Components\AudioComponent.h"

ACandyActor::ACandyActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CandyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CandyMesh"));
	CandyMesh->SetupAttachment(RootComponent);
}

void ACandyActor::BeginPlay()
{
	Super::BeginPlay();
}

void ACandyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator NewRotation = FRotator(0.f, 1.f, 0.f);

	FQuat QuatRotation = FQuat(NewRotation);

	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

void ACandyActor::OnInteract()
{
	UMyGameInstance* gameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	gameInstance->AddScore();

	Destroy();
}