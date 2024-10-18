// Fill out your copyright notice in the Description page of Project Settings.

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
