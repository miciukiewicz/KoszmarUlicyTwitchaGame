#include "MyHUD.h"
#include "MyGameInstance.h"
#include "Kismet\GameplayStatics.h"
#include "PlayerCharacter.h"

void UMyHUD::NativeConstruct()
{
	Super::NativeConstruct();

	ResumeButton->OnClicked.AddDynamic(this, &UMyHUD::ResumeGame);
	MenuButton->OnClicked.AddDynamic(this, &UMyHUD::MenuExit);
	BackTOMenuButton->OnClicked.AddDynamic(this, &UMyHUD::BackToMenu);
	RetryButton->OnClicked.AddDynamic(this, &UMyHUD::Retry);
	OptionsButton->OnClicked.AddDynamic(this, &UMyHUD::OpenSettings);
	BackToPauseButton->OnClicked.AddDynamic(this, &UMyHUD::BackToPauseMenu);

	BaseEndingCanvas->SetVisibility(ESlateVisibility::Hidden);
	GoodEndingCanvas->SetVisibility(ESlateVisibility::Hidden);
	OkEndingCanvas->SetVisibility(ESlateVisibility::Hidden);
	CarEndingCanvas->SetVisibility(ESlateVisibility::Hidden);
	KacEndingCanvas->SetVisibility(ESlateVisibility::Hidden);
	TimeEndingCanvas->SetVisibility(ESlateVisibility::Hidden);
	OptionCanvas->SetVisibility(ESlateVisibility::Hidden);
}

void UMyHUD::SetScoreText()
{
	UMyGameInstance* gameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	int score = gameInstance->GetScore();
	if (score == 9)
	{
		FString str = FString::Printf(TEXT("Wracaj do domu"), score);
		ScoreText->SetText(FText::FromString(str));
	}
	else
	{
		FString str = FString::Printf(TEXT("cuksy %d/9"), score);
		ScoreText->SetText(FText::FromString(str));
	}
}

void UMyHUD::SetTimer(int hours, int minutes)
{
	if (hours == 0)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("End sound cue"));

		FString str = "00:00";
		TimerText->SetText(FText::FromString(str));

		GetWorld()->GetTimerManager().SetTimer(
			HUDTimerVis, // handle to cancel timer at a later time
			this, // the owning object
			&UMyHUD::SetTimerVis, // function to call on elapsed
			0.5f, // float delay until elapsed
			true); // looping?
		return;
	}

	if (minutes < 10)
	{
		FString str = FString::Printf(TEXT("%d:0%d"), hours, minutes);
		TimerText->SetText(FText::FromString(str));
	}
	else
	{
		FString str = FString::Printf(TEXT("%d:%d"), hours, minutes);
		TimerText->SetText(FText::FromString(str));
	}
}

void UMyHUD::SetTimerVis()
{
	bHUDVis = !bHUDVis;
	TimerText->SetVisibility(bHUDVis ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UMyHUD::SetInteractVisibility(bool value)
{
	InteractText->SetVisibility(value ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UMyHUD::SetPauseMenuVisibility(bool value)
{
	if (value)
	{
		PlayerHUD->SetVisibility(ESlateVisibility::Hidden);
		PauseMenuHUD->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		PlayerHUD->SetVisibility(ESlateVisibility::Visible);
		PauseMenuHUD->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UMyHUD::SetStaminaProgressBar(float value)
{
	float staminaNormalized = value / 100.f;
	StaminaProgressBar->SetPercent(staminaNormalized);
}

void UMyHUD::SetStaminaProgressBarVisibility(bool value)
{
	StaminaProgressBar->SetVisibility(value ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void UMyHUD::ResumeGame()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("START"));

	SetPauseMenuVisibility(false);
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	APlayerController* playerCont = GetWorld()->GetFirstPlayerController();
	if (playerCont)
	{
		playerCont->bShowMouseCursor = false;
		playerCont->bEnableClickEvents = false;
		playerCont->bEnableMouseOverEvents = false;
	}
}

void UMyHUD::MenuExit()
{
	UGameplayStatics::OpenLevel(this, FName("MainMenu"), true);
}

void UMyHUD::SetEnding(int value)
{
	BaseEndingCanvas->SetVisibility(ESlateVisibility::Visible);

	switch (value)
	{
	case 1:
		GoodEndingCanvas->SetVisibility(ESlateVisibility::Visible);
		break;
	case 2:
		OkEndingCanvas->SetVisibility(ESlateVisibility::Visible);
		break;
	case 3:
		CarEndingCanvas->SetVisibility(ESlateVisibility::Visible);
		break;
	case 4:
		KacEndingCanvas->SetVisibility(ESlateVisibility::Visible);
		break;
	case 5:
		TimeEndingCanvas->SetVisibility(ESlateVisibility::Visible);
		break;
	}

}

void UMyHUD::BackToMenu()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BackToMenu"));

	UGameplayStatics::OpenLevel(this, FName("MainMenu"), true);
}

void UMyHUD::Retry()
{
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Retry"));

	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), true);
}

void UMyHUD::OpenSettings()
{
		if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("START"));

	PauseMenuHUD->SetVisibility(ESlateVisibility::Hidden);
	OptionCanvas->SetVisibility(ESlateVisibility::Visible);
}

void UMyHUD::BackToPauseMenu()
{
	OptionCanvas->SetVisibility(ESlateVisibility::Hidden);
	PauseMenuHUD->SetVisibility(ESlateVisibility::Visible);
}

void UMyHUD::SetValueMouseSlider(float value)
{
	MouseSlider->SetValue(value);
}

void UMyHUD::SetValueAudioSlider(float value)
{
	AudioSlider->SetValue(value);
}

void UMyHUD::SetValueFPSSlider(float value)
{
	FPSSlider->SetValue(value);
}

void UMyHUD::SetFPSCounterText(float value)
{
	FString floatStr = FString::SanitizeFloat(round(value));
	FPSCounter->SetText(FText::FromString(floatStr));
}
