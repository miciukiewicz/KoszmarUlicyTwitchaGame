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

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};