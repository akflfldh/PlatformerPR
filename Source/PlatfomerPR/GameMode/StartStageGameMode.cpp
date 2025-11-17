// Fill out your copyright notice in the Description page of Project Settings.


#include "StartStageGameMode.h"
#include"PlatfomerPR/CharacterController.h"


AStartStageGameMode::AStartStageGameMode() :EnergyCount(0)
{
}

void AStartStageGameMode::IncreaseEnergy()
{
	EnergyCount++;
}

int AStartStageGameMode::GetCurrentEnergy() const
{
	UE_LOG(LogTemp, Display, TEXT("assD"));
	return EnergyCount;
}

void AStartStageGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	UE_LOG(LogTemp, Display, TEXT("aD"));
	ACharacterController* PlayerController = Cast<ACharacterController>(NewPlayer);
	if (PlayerController)
	{
		UE_LOG(LogTemp, Display, TEXT("aD2"));
		PlayerController->RequsetStartStageSetting();
	}

}
