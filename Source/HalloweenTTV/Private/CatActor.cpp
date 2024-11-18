#include "CatActor.h"
#include "Components\AudioComponent.h"

ACatActor::ACatActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CatMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CatMesh"));
	CatMesh->SetupAttachment(RootComponent);

	CatSoundCue = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundCue"));
	CatSoundCue->SetupAttachment(CatMesh);
	CatSoundCue->bAutoActivate = true;

	InteractSound = CreateDefaultSubobject<UAudioComponent>(TEXT("InteractSound"));
	InteractSound->SetupAttachment(CatMesh);
	InteractSound->bAutoActivate = false;
}

void ACatActor::BeginPlay()
{
	Super::BeginPlay();
}

void ACatActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACatActor::OnInteract()
{
	InteractSound->Play();
}