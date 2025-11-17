// Fill out your copyright notice in the Description page of Project Settings.


#include "RollingObstacleManager.h"
#include"RoillingObstacle.h"

// Sets default values
ARollingObstacleManager::ARollingObstacleManager()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("SceneCom"));
}

// Called when the game starts or when spawned
void ARollingObstacleManager::BeginPlay()
{
	Super::BeginPlay();


	GetWorldTimerManager().SetTimer(TimerHandle, this, &ARollingObstacleManager::SpawnObstacle, SpawnDelay, true);

}

// Called every frame
void ARollingObstacleManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARollingObstacleManager::SpawnObstacle()
{

	if (bSpwanActiveFlag)
	{
		if (RoillingObstacleClass != nullptr)
		{
			FVector Location = GetActorLocation();
			FRotator Rotator = FRotator::ZeroRotator;
			ARoillingObstacle* RoillingObstacleActor = GetWorld()->SpawnActor<ARoillingObstacle>(RoillingObstacleClass, Location, Rotator);

			FVector TargetLocation = GetActorLocation() + TargetLocationOffset;

			RoillingObstacleActor->SetTargetLocation(TargetLocation);
			RoillingObstacleActor->SetSpeed(ObstacleSpeed);


		}



	}


}

