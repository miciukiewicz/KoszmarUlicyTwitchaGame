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

private:
	FVector vDirection;
	FVector vStartLocation;
	float fTotalDistance;
};