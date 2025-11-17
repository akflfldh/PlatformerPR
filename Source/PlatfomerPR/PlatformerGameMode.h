// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlatformerGameMode.generated.h"

/**
 *
 */
UCLASS()
class PLATFOMERPR_API APlatformerGameMode : public AGameModeBase
{
	GENERATED_BODY()


public:
	APlatformerGameMode();


	void IncreaseCollectedCrystalCount();
	int GetCurrentCollectedCrystalCount() const;

	void IncreaseCollectedCoinCount();
	int GetCurrentCollectedCoinCount() const;


	virtual void PostLogin(APlayerController* NewPlayer) override;
private:


	int CollectedCrystalCount;
	int CollectedCoinCount;

};
