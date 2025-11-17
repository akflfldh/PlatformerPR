// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterController.h"
#include<Blueprint/UserWidget.h>
#include<PlatfomerPR/PlatformerGameMode.h>
#include<PlatfomerPR/GameMode/StartStageGameMode.h>

void ACharacterController::RequsetStartStageSetting()
{
	UE_LOG(LogTemp, Display, TEXT("aD5"));
	if (StartStageWidgetClass)
	{
		UE_LOG(LogTemp, Display, TEXT("aD3"));
		StartStageWidget = CreateWidget(this, StartStageWidgetClass);
	}

	if (StartStageWidget)
	{
		UE_LOG(LogTemp, Display, TEXT("aD4"));
		StartStageWidget->AddToViewport();
	}
}

void ACharacterController::RequestStageSetting()
{
	if (HUDWidgetClass != nullptr)
	{

		HUDWidget = CreateWidget(this, HUDWidgetClass);
	}

	if (HUDWidget)
	{
		HUDWidget->AddToViewport();
	}


}

void ACharacterController::BeginPlay()
{

	Super::BeginPlay();




}

int ACharacterController::GetCrystalCount()
{
	//gamemode에서 crystal count를 가져와야지.

	APlatformerGameMode* gameMode = Cast<APlatformerGameMode>(GetWorld()->GetAuthGameMode());
	if (gameMode)
	{
		return		gameMode->GetCurrentCollectedCrystalCount();
	}
	return 0;
}

int ACharacterController::GetCoinCount()
{
	APlatformerGameMode* gameMode = Cast<APlatformerGameMode>(GetWorld()->GetAuthGameMode());
	if (gameMode)
	{
		return	gameMode->GetCurrentCollectedCoinCount();
	}
	return 0;
}

int ACharacterController::GetEnergyCount()
{
	AStartStageGameMode* gameMode = Cast< AStartStageGameMode>(GetWorld()->GetAuthGameMode());
	if (gameMode)
	{

		return gameMode->GetCurrentEnergy();
	}

	return 0;
}
