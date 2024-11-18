#include "MyGameInstance.h"

void UMyGameInstance::AddScore()
{
	Score += 1;

	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Score: %d"), Score));
}

int UMyGameInstance::GetScore()
{
	return Score;
}

void UMyGameInstance::ResetScore()
{
	Score = 0;
}