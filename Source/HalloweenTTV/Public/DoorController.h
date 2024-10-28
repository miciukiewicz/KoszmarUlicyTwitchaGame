#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/TimelineComponent.h"
#include "DoorController.generated.h"

UCLASS()
class HALLOWEENTTV_API ADoorController : public AActor
{
	GENERATED_BODY()

public:
	ADoorController();
	void OnInteract();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	FTimeline Timeline;
	UPROPERTY(EditAnywhere)
	UCurveFloat* CurveFloat;

	UPROPERTY(VisibleAnywhere)
	bool bIsDoorClosed = true;

	UPROPERTY(EditAnywhere)
	float DoorRotateAngle = 90.f;

	UFUNCTION()
	void OpenDoor(float value);

	UPROPERTY(EditAnywhere)
	bool LockedDoor = false;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* SoundCue;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* DoorSound;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* DoorMesh;

	bool bSoundPlayed = false;

	float fAtStartRotation;

	FTimerHandle DelayForSoundCue;

	void PlaySoundCue();

};
