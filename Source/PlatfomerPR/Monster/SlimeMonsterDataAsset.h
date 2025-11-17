// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlatfomerPR/MonsterBaseDataAsset.h"
#include "SlimeMonsterDataAsset.generated.h"

/**
 *
 */
UCLASS()
class PLATFOMERPR_API USlimeMonsterDataAsset : public UMonsterBaseDataAsset
{
	GENERATED_BODY()


public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Slime Attack")
	TObjectPtr<UMaterialInstance> AttackLandingWarningDecalMaterial;







};
