#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

UCLASS()
class HALLOWEENTTV_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	void AddScore();
	int GetScore();
	void ResetScore();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SavedSensValue = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SavedAudioValue = 1.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SavedFPSValue = 60.f;

private:
	int Score;
};
