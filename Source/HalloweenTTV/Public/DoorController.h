// Fill out your copyright notice in the Description page of Project Settings.

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
	// Sets default values for this actor's properties
	ADoorController();
	void OnInteract();

protected:
	// Called when the game starts or when spawned
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

private:
	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* DoorMesh;

	bool bSoundPlayed = false;
};
