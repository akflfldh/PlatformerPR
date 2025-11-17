// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformerGameMode.h"
#include"PlatfomerPR/CharacterController.h"
APlatformerGameMode::APlatformerGameMode() :CollectedCrystalCount(0)
{
}

void APlatformerGameMode::IncreaseCollectedCrystalCount()
{
	CollectedCrystalCount++;
	UE_LOG(LogTemp, Display, TEXT("Crystal Count :  %d"), CollectedCrystalCount);
}

int APlatformerGameMode::GetCurrentCollectedCrystalCount() const
{
	return CollectedCrystalCount;
}

void APlatformerGameMode::IncreaseCollectedCoinCount()
{
	CollectedCoinCount++;
}

int APlatformerGameMode::GetCurrentCollectedCoinCount() const
{
	return CollectedCoinCount;
}

void APlatformerGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ACharacterController* Player = Cast<ACharacterController>(NewPlayer);

	if (Player)
	{
		Player->RequestStageSetting();
	}



}
