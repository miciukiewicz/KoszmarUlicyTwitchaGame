// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorController.h"
#include "Components\BoxComponent.h"
#include "Components\AudioComponent.h"
#include "Components\SceneComponent.h"

// Sets default values
ADoorController::ADoorController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	DoorMesh->SetupAttachment(RootComponent);

	SoundCue = CreateDefaultSubobject<UAudioComponent>(TEXT("BehindDoorSound"));
	SoundCue->SetupAttachment(DoorMesh);
	SoundCue->SetRelativeLocation(FVector(45.f, -250.f, 125.f));

	DoorSound = CreateDefaultSubobject<UAudioComponent>(TEXT("DoorSound"));
	DoorSound->SetupAttachment(DoorMesh);
	DoorSound->SetRelativeLocation(FVector(45.f, 0.f, 90.f));

	DoorSound->bAutoActivate = false;
	SoundCue->bAutoActivate = false;
}

void ADoorController::OnInteract()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Trying to open the door"));

	if (LockedDoor)
	{
		if (SoundCue == nullptr) return;

		if (bSoundPlayed == false)
		{
			bSoundPlayed = true;
			SoundCue->Play();
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

// Called when the game starts or when spawned
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

}

// Called every frame
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
