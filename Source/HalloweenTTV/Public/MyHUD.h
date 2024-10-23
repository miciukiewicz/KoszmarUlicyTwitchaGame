#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components\TextBlock.h"
#include "MyHUD.generated.h"

UCLASS()
class HALLOWEENTTV_API UMyHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ScoreText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* TimerText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* InteractText;

	void SetScoreText();

	void SetTimer(int hours, int minutes);

	FTimerHandle HUDTimerVis;

	void SetTimerVis();

	void SetInteractVisibility(bool value);

	bool bHUDVis = true;
};