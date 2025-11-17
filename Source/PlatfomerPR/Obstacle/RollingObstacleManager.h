// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "RollingObstacleManager.generated.h"


class ARoillingObstacle;

UCLASS()
class PLATFOMERPR_API ARollingObstacleManager : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARollingObstacleManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere)
	TSubclassOf<ARoillingObstacle> RoillingObstacleClass;


	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget))
	FVector SpawnLocationOffset = { 0,0,0 };

	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget))
	FVector TargetLocationOffset = { 0,0,0 };


	UPROPERTY(EditAnywhere)
	float SpawnDelay = 10.0f;

	UPROPERTY(EditAnywhere)
	bool bSpwanActiveFlag = false;

	UPROPERTY(EditAnywhere)
	float ObstacleSpeed = 30.0f;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	void SpawnObstacle();


private:

	FTimerHandle TimerHandle;



};
