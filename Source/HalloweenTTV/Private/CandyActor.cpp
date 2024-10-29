#include "CandyActor.h"
#include "MyGameInstance.h"
#include "Components\BoxComponent.h"
#include "PlayerCharacter.h"
#include "Components\AudioComponent.h"

ACandyActor::ACandyActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CandyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CandyMesh"));
	CandyMesh->SetupAttachment(RootComponent);

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(CandyMesh);
}

void ACandyActor::BeginPlay()
{
	Super::BeginPlay();

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ACandyActor::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ACandyActor::OnEndOverlap);
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

void ACandyActor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);

	//if (player)
	//{
	//	player->SetInteractVisibility(true);
	//}
}

void ACandyActor::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);

	//if (player)
	//{
	//	player->SetInteractVisibility(false);
	//}
}