#include "MyHUD.h"
#include "MyGameInstance.h"

void UMyHUD::SetScoreText()
{
	UMyGameInstance* gameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	int score = gameInstance->GetScore();
	FString str = FString::Printf(TEXT("Cuksy %d/8"), score);
	ScoreText->SetText(FText::FromString(str));
}

void UMyHUD::SetTimer(int hours, int minutes)
{
	if (hours == 0)
	{
		FString str = FString::Printf(TEXT("00:00"), hours, minutes);
		TimerText->SetText(FText::FromString(str));

		GetWorld()->GetTimerManager().SetTimer(
			HUDTimerVis, // handle to cancel timer at a later time
			this, // the owning object
			&UMyHUD::SetTimerVis, // function to call on elapsed
			0.5f, // float delay until elapsed
			true); // looping?
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
