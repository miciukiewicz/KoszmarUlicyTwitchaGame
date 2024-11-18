#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundJumpscareTemplateActor.generated.h"

UCLASS()
class HALLOWEENTTV_API ASoundJumpscareTemplateActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ASoundJumpscareTemplateActor();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxCollider;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* JumpscareSoundCue;

	UFUNCTION()
	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnFinishedSound();
private:
	bool bSoundPlayed = false;
}; 
