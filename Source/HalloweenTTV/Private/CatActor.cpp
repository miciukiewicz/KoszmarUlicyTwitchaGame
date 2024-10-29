// Fill out your copyright notice in the Description page of Project Settings.

#include "Components\AudioComponent.h"
#include "CatActor.h"

// Sets default values
ACatActor::ACatActor()
{
	PrimaryActorTick.bCanEverTick = true;

	CatMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CatMesh"));
	CatMesh->SetupAttachment(RootComponent);

	SoundCue = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundCue"));
	SoundCue->SetupAttachment(CatMesh);
	SoundCue->bAutoActivate = true;

	InteractSound = CreateDefaultSubobject<UAudioComponent>(TEXT("InteractSound"));
	InteractSound->SetupAttachment(CatMesh);
	InteractSound->bAutoActivate = false;

}

// Called when the game starts or when spawned
void ACatActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACatActor::OnInteract()
{
	InteractSound->Play();
}

// Called every frame
void ACatActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

