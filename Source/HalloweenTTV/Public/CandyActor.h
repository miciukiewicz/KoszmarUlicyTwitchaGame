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
};
