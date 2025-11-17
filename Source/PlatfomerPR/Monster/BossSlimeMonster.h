// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlimeMonster.h"
#include "BossSlimeMonster.generated.h"
class UDecalComponent;
/**
 *
 */
UCLASS()
class PLATFOMERPR_API ABossSlimeMonster : public ASlimeMonster
{
	GENERATED_BODY()

public:
	ABossSlimeMonster();

	virtual void Attack(AActor* actor) override;
	void CancelAttack() override;

	virtual void OnMovementModeChanged(EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0) override;

	virtual void OnStomped_Implementation(AActor* StompingActor) override;


private:

	virtual void AttackBeginNotify() override;
	void SpawnAttackWaringDecal(const FVector& SpawnLocation);


	FVector LaunchVelocity;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float AttackRadius = 50.0f;


	UPROPERTY(EditAnywhere, Category = "Attack")
	float KnockbackXYStrength = 200.0F;

	UPROPERTY(EditAnywhere, Category = "Attack")
	float KnockbackZStrength = 500.0f;



	TObjectPtr < UDecalComponent> AttackLandingSpawnedDecal = nullptr;
};
