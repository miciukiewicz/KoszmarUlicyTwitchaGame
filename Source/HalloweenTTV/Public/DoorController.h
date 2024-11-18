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

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* DoorMesh;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* BehindDoorSoundCue;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* DoorSoundCue;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere)
	UCurveFloat* CurveFloat;

	UPROPERTY(EditAnywhere)
	bool bLockedDoor = false;

	UPROPERTY(EditAnywhere)
	float fDoorRotateAngle = 90.f;

	UFUNCTION()
	void OpenDoor(float value);

private:
	bool bSoundPlayed = false;
	bool bIsDoorClosed = true;
	float fAtStartRotation;
	FTimerHandle DelayForSoundCue;
	FTimeline TimelineOpeningDoors;
	void PlaySoundCue();
};