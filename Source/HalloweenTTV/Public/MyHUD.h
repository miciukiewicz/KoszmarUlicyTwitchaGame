#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyHUD.generated.h"

UCLASS()
class HALLOWEENTTV_API UMyHUD : public UUserWidget
{
	GENERATED_BODY()

	void NativeConstruct();

public:

	//canvas
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* PlayerHUDCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* PauseMenuCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* BaseEndingCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* GoodEndingCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* OkEndingCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* CarEndingCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* KacEndingCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* TimeEndingCanvas;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UCanvasPanel* OptionCanvas;

	//in-game HUD and logic
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* ScoreText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* TimerText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* InteractText;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UProgressBar* StaminaProgressBar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* BackTOMenuButton;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UButton* RetryButton;

	UFUNCTION(BlueprintCallable)
	void SetEnding(int value);

	//options
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* ResumeButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* MenuButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* OptionsButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UButton* BackToPauseButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class USlider* MouseSlider;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class USlider* AudioSlider;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class USlider* FPSSlider;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	class UTextBlock* FPSCounter;

	UFUNCTION()
	void ResumeGame();

	UFUNCTION()
	void MenuExit();

	UFUNCTION(BlueprintCallable)
	void SetValueMouseSlider(float value);

	UFUNCTION(BlueprintCallable)
	void SetValueAudioSlider(float value);

	UFUNCTION(BlueprintCallable)
	void SetFPSCounterText(float value);

	UFUNCTION(BlueprintCallable)
	void SetValueFPSSlider(float value);

	UFUNCTION(BlueprintCallable)
	void BackToMenu();

	UFUNCTION(BlueprintCallable)
	void Retry();

	UFUNCTION(BlueprintCallable)
	void OpenSettings();

	UFUNCTION(BlueprintCallable)
	void BackToPauseMenu();

	//getters and setters
	void SetScoreText();
	void SetTimer(int hours, int minutes);
	void SetTimerVis();
	void SetInteractVisibility(bool value);
	void SetPauseMenuVisibility(bool value);
	void SetStaminaProgressBar(float value);
	void SetStaminaProgressBarVisibility(bool value);
	FTimerHandle HUDTimerVis;
	bool bHUDVis = true;
};