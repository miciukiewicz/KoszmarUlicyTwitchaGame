#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CandyActor.generated.h"

UCLASS()
class HALLOWEENTTV_API ACandyActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACandyActor();

	virtual void Tick(float DeltaTime) override;

	void OnInteract();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	class UStaticMeshComponent* CandyMesh;

	UPROPERTY(EditAnywhere)
	class UBoxComponent* BoxComponent;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
