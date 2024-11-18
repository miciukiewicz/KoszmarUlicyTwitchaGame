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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ValueFromOptions;

protected:
	virtual void BeginPlay() override;

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

	UPROPERTY(EditAnywhere, Category = "EnhancedInput")
	class UInputAction* ResetPositionAction;

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TSubclassOf<UMyHUD> HUDClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UMyHUD* HUDWidget;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* StepSoundCue;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* PickUpSoundCue;

	UPROPERTY(EditAnywhere)
	class UAudioComponent* EndTimerSoundCue;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> EndgameGhostActor;

	UPROPERTY(EditAnywhere)
	float fInteractLineTraceLength = 350.f;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact();
	void ZoomIn();
	void ZoomOut();
	void PauseMenuVis();
	void SprintStart();
	void SprintEnd();
	void ResetPosition();
	FTimerHandle thFootsteps;
	FTimerHandle thHUDTime;
	FTimerHandle thUseSprintEnergy;
	FTimerHandle thRegenSprintEnergy;

private:
	void SetTimerOnHUD();
	void PlayFootstepSound();
	void SetInteractVisibility(bool value);
	float fSprintEnergy = 100.f;
	float fWalkSpeed;
	int iHours = 20;
	int iMinutes = 0;
	bool bIsRunning = false;
};