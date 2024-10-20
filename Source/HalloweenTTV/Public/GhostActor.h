// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GhostActor.generated.h"

UCLASS()
class HALLOWEENTTV_API AGhostActor : public AActor
{
	GENERATED_BODY()
	
public:
	AGhostActor();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* GhostMesh;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* GhostSoundCue;

	UPROPERTY(EditAnywhere)
	int GhostSpeed;

	FVector Direction;
	FVector StartLocation;
	float TotalDistance;
};