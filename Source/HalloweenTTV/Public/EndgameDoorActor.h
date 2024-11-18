#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EndgameDoorActor.generated.h"

UCLASS()
class HALLOWEENTTV_API AEndgameDoorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AEndgameDoorActor();
	virtual void Tick(float DeltaTime) override;
	void OnInteract();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* DoorSoundCue;

	UPROPERTY(EditAnywhere)
	class UStaticMeshComponent* EndgameDoorMesh;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;
};