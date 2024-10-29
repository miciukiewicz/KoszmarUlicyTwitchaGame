#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CatActor.generated.h"

UCLASS()
class HALLOWEENTTV_API ACatActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ACatActor();

	virtual void Tick(float DeltaTime) override;

	void OnInteract();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "Mesh")
	class USkeletalMeshComponent* CatMesh;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* SoundCue;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* InteractSound;


};
