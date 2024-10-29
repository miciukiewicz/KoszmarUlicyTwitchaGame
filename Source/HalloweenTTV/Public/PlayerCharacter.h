#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MyHUD.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class HALLOWEENTTV_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void SetInteractVisibility(bool value);

	bool PauseMenu = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ValueFromOptions;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float InteractLineTraceLength = 350.f; 

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UMyHUD> HUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UMyHUD* HUDWidget;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputMappingContext* InputMapping;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* MovementAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* InteractAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* ZoomAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* PauseMenuAction;

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* SprintAction;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* StepSoundCue;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* PickUpSound;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* TimerSound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ProjectileClass;

	void PlayFootstepSound();
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact();
	void ZoomIn();
	void ZoomOut();
	void PauseMenuVis();
	void SprintStart();
	void SprintEnd();
	float WalkSpeed;
	FTimerHandle FootstepTimerHandle;
	FTimerHandle HUDTimer;
	FTimerHandle useSprintEnergy;
	FTimerHandle regenSprintEnergy;
	float sprintEnergy = 100.f;
	void SetTimerOnHUD();
	int hours = 20;
	int minutes = 0;
	bool isRunning = false;
};
