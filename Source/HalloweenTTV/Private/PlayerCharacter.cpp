#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components\AudioComponent.h"
#include "DoorController.h"
#include "Kismet\GameplayStatics.h"
#include "CandyActor.h"
#include "GhostActor.h"
#include "EndgameDoorActor.h"


APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	Camera->SetupAttachment(RootComponent);
	Camera->bUsePawnControlRotation = true;

	StepSoundCue = CreateDefaultSubobject<UAudioComponent>(TEXT("AudioComponent"));
	StepSoundCue->SetupAttachment(Camera);
	StepSoundCue->SetRelativeLocation(FVector(0.f, 0.f, -44.f));
	StepSoundCue->bAutoActivate = false;

	PickUpSound = CreateDefaultSubobject<UAudioComponent>(TEXT("PickUpSoundCue"));
	PickUpSound->SetupAttachment(Camera);
	PickUpSound->bAutoActivate = false;

	TimerSound = CreateDefaultSubobject<UAudioComponent>(TEXT("TimerSound"));
	TimerSound->SetupAttachment(Camera);
	TimerSound->bAutoActivate = false;
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(
		FootstepTimerHandle, // handle to cancel timer at a later time
		this, // the owning object
		&APlayerCharacter::PlayFootstepSound, // function to call on elapsed
		0.5f, // float delay until elapsed
		true); // looping?

	GetWorld()->GetTimerManager().SetTimer(
		HUDTimer,
		this,
		&APlayerCharacter::SetTimerOnHUD,
		0.5f,
		true);


	if (HUDClass)
	{
		HUDWidget = CreateWidget<UMyHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0), HUDClass);
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
			HUDWidget->SetInteractVisibility(false);
			HUDWidget->SetPauseMenuVisibility(false);

		}
	}
}

void APlayerCharacter::PlayFootstepSound()
{
	double vel = GetVelocity().Length();
	if (vel > 5 || vel < -5)
	{
		StepSoundCue->Play();
	}
}

void APlayerCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();

	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.Y);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.X);
}

void APlayerCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();

	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void APlayerCharacter::Interact()
{
	if (Camera == nullptr) return;

	FHitResult HitResult;
	FVector Start = Camera->GetComponentLocation();
	FVector End = Start + Camera->GetForwardVector() * InteractLineTraceLength;
	GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECollisionChannel::ECC_Visibility);

	ADoorController* door = Cast<ADoorController>(HitResult.GetActor());
	ACandyActor* candy = Cast<ACandyActor>(HitResult.GetActor());
	AEndgameDoorActor* endgameDoor = Cast<AEndgameDoorActor>(HitResult.GetActor());

	if (door)
	{
		door->OnInteract();
	}
	else if (candy)
	{
		candy->OnInteract();
		HUDWidget->SetScoreText();
		PickUpSound->Play();
	}
	else if (endgameDoor)
	{
		endgameDoor->OnInteract();
	}
}

void APlayerCharacter::ZoomOut()
{
	Camera->SetFieldOfView(90.f);
}

void APlayerCharacter::ZoomIn()
{
	Camera->SetFieldOfView(45.f);
}

void APlayerCharacter::PauseMenuVis()
{
	HUDWidget->SetPauseMenuVisibility(true);
	PauseMenu = true;
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	APlayerController* playerCont = GetWorld()->GetFirstPlayerController();
	if (playerCont)
	{
		playerCont->bShowMouseCursor = true;
		playerCont->bEnableClickEvents = true;
		playerCont->bEnableMouseOverEvents = true;
	}
}

void APlayerCharacter::SetTimerOnHUD()
{
	minutes++;
	if (minutes == 60)
	{
		hours++;
		minutes = 0;
	}

	if (hours == 24)
	{
		hours = 0;
		GetWorldTimerManager().ClearTimer(HUDTimer);
		TimerSound->Play();
		GetWorld()->SpawnActor<AActor>(ProjectileClass, FVector(1500, -110, 190), GetActorRotation());
	}

	HUDWidget->SetTimer(hours, minutes);
}

void APlayerCharacter::SetInteractVisibility(bool value)
{
	HUDWidget->SetInteractVisibility(value);
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(InputMapping, 0);
		}
	}

	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MovementAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Look);
		EnhancedInputComponent->BindAction(InteractAction, ETriggerEvent::Triggered, this, &APlayerCharacter::Interact);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Started, this, &APlayerCharacter::ZoomIn);
		EnhancedInputComponent->BindAction(ZoomAction, ETriggerEvent::Completed, this, &APlayerCharacter::ZoomOut);
		EnhancedInputComponent->BindAction(PauseMenuAction, ETriggerEvent::Triggered, this, &APlayerCharacter::PauseMenuVis);
	}
}