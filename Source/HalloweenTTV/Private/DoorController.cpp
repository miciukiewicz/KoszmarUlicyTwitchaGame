#include "DoorController.h"
#include "Components\BoxComponent.h"
#include "Components\AudioComponent.h"
#include "Components\SceneComponent.h"
#include "PlayerCharacter.h"

ADoorController::ADoorController()
{
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(RootComponent);

	SoundCue = CreateDefaultSubobject<UAudioComponent>(TEXT("BehindDoorSound"));
	SoundCue->SetupAttachment(DoorMesh);
	SoundCue->SetRelativeLocation(FVector(45.f, -250.f, 125.f));
	SoundCue->bAutoActivate = false;

	DoorSound = CreateDefaultSubobject<UAudioComponent>(TEXT("DoorSound"));
	DoorSound->SetupAttachment(DoorMesh);
	DoorSound->SetRelativeLocation(FVector(45.f, 0.f, 90.f));
	DoorSound->bAutoActivate = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(DoorMesh);
}

void ADoorController::OnInteract()
{
	if (DoorSound != nullptr)
	{
		DoorSound->Play();
	}

	if (LockedDoor)
	{
		if (SoundCue == nullptr) return;

		if (bSoundPlayed == false)
		{
			bSoundPlayed = true;

			GetWorld()->GetTimerManager().SetTimer(
				DelayForSoundCue, // handle to cancel timer at a later time
				this, // the owning object
				&ADoorController::PlaySoundCue, // function to call on elapsed
				1.25f, // float delay until elapsed
				false); // looping?

			return;
		}
		return;
	}
		

	if (bIsDoorClosed)
	{
		Timeline.Play();
	}
	else
	{
		Timeline.Reverse();
	}

	bIsDoorClosed = !bIsDoorClosed;
}

void ADoorController::BeginPlay()
{
	Super::BeginPlay();

	fAtStartRotation = DoorMesh->GetRelativeRotation().Yaw;
	
	if (CurveFloat)
	{
		FOnTimelineFloat TimelineProgress;
		TimelineProgress.BindDynamic(this, &ADoorController::OpenDoor);
		Timeline.AddInterpFloat(CurveFloat, TimelineProgress);
	}

	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADoorController::OnOverlapBegin);
	BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ADoorController::OnEndOverlap);
}

void ADoorController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Timeline.TickTimeline(DeltaTime);
}

void ADoorController::OpenDoor(float value)
{
	FRotator Rot = FRotator(0.f, fAtStartRotation + (DoorRotateAngle * value), 0.f);

	DoorMesh->SetRelativeRotation(Rot);
}

void ADoorController::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	//APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);

	//if (player)
	//{
	//	player->SetInteractVisibility(true);
	//}
}

void ADoorController::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//APlayerCharacter* player = Cast<APlayerCharacter>(OtherActor);

	//if (player)
	//{
	//	player->SetInteractVisibility(false);
	//}
}

void ADoorController::PlaySoundCue()
{
	SoundCue->Play();
}
