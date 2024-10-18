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

private:
	int Score;
	
};
