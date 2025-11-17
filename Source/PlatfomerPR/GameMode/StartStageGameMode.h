// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "StartStageGameMode.generated.h"

/**
 *
 */
UCLASS()
class PLATFOMERPR_API AStartStageGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	AStartStageGameMode();

	void IncreaseEnergy();
	int GetCurrentEnergy() const;

	void PostLogin(APlayerController* NewPlayer) override;
private:

	int EnergyCount;


};
