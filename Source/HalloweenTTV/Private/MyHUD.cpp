
#include "MyGameInstance.h"
#include "MyHUD.h"

void UMyHUD::SetScoreText()
{
	UMyGameInstance* gameInstance = Cast<UMyGameInstance>(GetWorld()->GetGameInstance());
	int score = gameInstance->GetScore();
	FString str = FString::Printf(TEXT("Cukierki %d / 8"), score);
	ScoreText->SetText(FText::FromString(str));
}
