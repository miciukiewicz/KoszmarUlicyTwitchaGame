
#include "SoundJumpscareTemplateActor.h"
#include "Components\BoxComponent.h"
#include "Components\AudioComponent.h"
#include "PlayerCharacter.h"
#include "DrawDebugHelpers.h"

ASoundJumpscareTemplateActor::ASoundJumpscareTemplateActor()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	BoxCollider->SetupAttachment(RootComponent);

	JumpscareSoundCue = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	JumpscareSoundCue->SetupAttachment(BoxCollider);
	JumpscareSoundCue->bAutoActivate = false;
}

void ASoundJumpscareTemplateActor::BeginPlay()
{
	Super::BeginPlay();

	DrawDebugSphere(GetWorld(), GetActorLocation(), 25.f, 24, FColor::Red, false, 10.f);

	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ASoundJumpscareTemplateActor::OnBoxBeginOverlap);
	JumpscareSoundCue->OnAudioFinished.AddDynamic(this, &ASoundJumpscareTemplateActor::OnFinishedSound);
}

void ASoundJumpscareTemplateActor::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bSoundPlayed == false && OtherActor == Cast<APlayerCharacter>(OtherActor))
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Actor overlapping -> %s"), *OtherActor->GetName()));

		bSoundPlayed = true;
		JumpscareSoundCue->Play();
	}
}

void ASoundJumpscareTemplateActor::OnFinishedSound()
{
	Destroy();
}

void ASoundJumpscareTemplateActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}