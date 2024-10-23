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

	UPROPERTY(EditAnywhere)
	class UAudioComponent* SoundCue;

	void OnInteract();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Mesh")
	class UStaticMeshComponent* DoorMesh;
};