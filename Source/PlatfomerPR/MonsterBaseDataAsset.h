// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "MonsterBaseDataAsset.generated.h"


/**
 *
 */
UCLASS()
class PLATFOMERPR_API UMonsterBaseDataAsset : public UDataAsset
{
	GENERATED_BODY()


public:


	UPROPERTY(EditAnywhere)
	float MaxHealth;

	UPROPERTY(EditAnywhere)
	float SightRadius;


	UPROPERTY(EditAnywhere)
	float LoseSightRadius;

	UPROPERTY(EditAnywhere)
	float PeripheralVisionAngleDegrees;


private:




};
