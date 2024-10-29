#include "EndgameDoorActor.h"
#include "PlayerCharacter.h"
#include "Components\BoxComponent.h"
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

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(DoorMesh);
}

void AEndgameDoorActor::OnInteract()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("END GAME"));

	if (SoundCue != nullptr)
		SoundCue->Play();
}

void AEndgameDoorActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEndgameDoorActor::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &AEndgameDoorActor::OnEndOverlap);
}

void AEndgameDoorActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEndgameDoorActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);

	//if (player)
	//{
	//	player->SetInteractVisibility(true);
	//}
}

void AEndgameDoorActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);

	//if (player)
	//{
	//	player->SetInteractVisibility(false);
	//}
}