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

	BehindDoorSoundCue = CreateDefaultSubobject<UAudioComponent>(TEXT("BehindDoorSound"));
	BehindDoorSoundCue->SetupAttachment(DoorMesh);
	BehindDoorSoundCue->SetRelativeLocation(FVector(45.f, -250.f, 125.f));
	BehindDoorSoundCue->bAutoActivate = false;

	DoorSoundCue = CreateDefaultSubobject<UAudioComponent>(TEXT("DoorSound"));
	DoorSoundCue->SetupAttachment(DoorMesh);
	DoorSoundCue->SetRelativeLocation(FVector(45.f, 0.f, 90.f));
	DoorSoundCue->bAutoActivate = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	BoxComponent->SetupAttachment(DoorMesh);
}

void ADoorController::OnInteract()
{
	if (DoorSoundCue != nullptr)
	{
		DoorSoundCue->Play();
	}

	if (bLockedDoor)
	{
		if (BehindDoorSoundCue == nullptr) return;

		if (bSoundPlayed == false)
		{
			bSoundPlayed = true;

			GetWorld()->GetTimerManager().SetTimer(
				DelayForSoundCue, 
				this, 
				&ADoorController::PlaySoundCue, 
				1.25f, 
				false);

			return;
		}
		return;
	}

	if (bIsDoorClosed)
	{
		TimelineOpeningDoors.Play();
	}
	else
	{
		TimelineOpeningDoors.Reverse();
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
		TimelineOpeningDoors.AddInterpFloat(CurveFloat, TimelineProgress);
	}
}

void ADoorController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TimelineOpeningDoors.TickTimeline(DeltaTime);
}

void ADoorController::OpenDoor(float value)
{
	FRotator Rot = FRotator(0.f, fAtStartRotation + (fDoorRotateAngle * value), 0.f);

	DoorMesh->SetRelativeRotation(Rot);
}

void ADoorController::PlaySoundCue()
{
	BehindDoorSoundCue->Play();
}