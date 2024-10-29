#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components\TextBlock.h"
#include <Components\CanvasPanel.h>
#include "Components\ProgressBar.h"
#include <Components\Button.h>
#include "Components\Slider.h"
#include "MyHUD.generated.h"

UCLASS()
class HALLOWEENTTV_API UMyHUD : public UUserWidget
{
	GENERATED_BODY()

	void NativeConstruct();

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ScoreText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* TimerText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* InteractText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* PlayerHUD;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* PauseMenuHUD;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* ResumeButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* MenuButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UProgressBar* StaminaProgressBar;

	void SetScoreText();

	void SetTimer(int hours, int minutes);

	FTimerHandle HUDTimerVis;

	void SetTimerVis();

	void SetInteractVisibility(bool value);

	void SetPauseMenuVisibility(bool value);

	void SetStaminaProgressBar(float value);

	void SetStaminaProgressBarVisibility(bool value);

	UFUNCTION()
	void ResumeGame();

	UFUNCTION()
	void MenuExit();

	bool bHUDVis = true;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* BaseEndingCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* GoodEndingCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* OkEndingCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* CarEndingCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* KacEndingCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* TimeEndingCanvas;

	UFUNCTION(BlueprintCallable)
	void SetEnding(int value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* BackTOMenuButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	UButton* RetryButton;

	UFUNCTION(BlueprintCallable)
	void BackToMenu();

	UFUNCTION(BlueprintCallable)
	void Retry();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UCanvasPanel* OptionCanvas;

	UFUNCTION(BlueprintCallable)
	void OpenSettings();

	UFUNCTION(BlueprintCallable)
	void BackToPauseMenu();

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* OptionsButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UButton* BackToPauseButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	USlider* MouseSlider;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	USlider* AudioSlider;

	UFUNCTION(BlueprintCallable)
	void SetValueMouseSlider(float value);

	UFUNCTION(BlueprintCallable)
	void SetValueAudioSlider(float value);
};