// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components\TextBlock.h"
#include "MyHUD.generated.h"

/**
 * 
 */
UCLASS()
class HALLOWEENTTV_API UMyHUD : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UTextBlock* ScoreText;

	void SetScoreText();
};
