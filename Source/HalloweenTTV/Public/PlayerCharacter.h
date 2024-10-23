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

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	float InteractLineTraceLength = 350.f; 

	UPROPERTY(EditAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMyHUD> HUDClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
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
	FTimerHandle FootstepTimerHandle;
	FTimerHandle HUDTimer;
	void SetTimerOnHUD();
	int hours = 20;
	int minutes = 0;
};
