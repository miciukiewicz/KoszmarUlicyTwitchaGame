// Fill out your copyright notice in the Description page of Project Settings.

#include "SoundJumpscareTemplateActor.h"
#include "Components\BoxComponent.h"
#include "Components\AudioComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
ASoundJumpscareTemplateActor::ASoundJumpscareTemplateActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(RootComponent);

	SoundCue = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	SoundCue->SetupAttachment(BoxCollider);
	SoundCue->bAutoActivate = false;

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ASoundJumpscareTemplateActor::OnBoxBeginOverlap);
}

// Called when the game starts or when spawned
void ASoundJumpscareTemplateActor::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugSphere(GetWorld(), GetActorLocation(), 25.f, 24, FColor::Red, false, 10.f);
}

void ASoundJumpscareTemplateActor::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bSoundPlayed == false)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Actor overlapping -> %s"), *OtherActor->GetName()));

		bSoundPlayed = true;
		SoundCue->Play();
	}
	else
	{
		//FlushPersistentDebugLines(GetWorld());
		Destroy();
	}
}

// Called every frame
void ASoundJumpscareTemplateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

