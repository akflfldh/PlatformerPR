// Fill out your copyright notice in the Description page of Project Settings.


#include "FallablePlatformController.h"

void AFallablePlatformController::BeginPlay()
{
	Super::BeginPlay();
}

AFallablePlatformController::AFallablePlatformController()
{

	RootComponent = CreateDefaultSubobject<USceneComponent>(FName("SceneCom"));


}

void AFallablePlatformController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AFallablePlatformController::OnActivate()
{
	UE_LOG(LogTemp, Display, TEXT("FallablePlatformController"));


	ResetPlatformList();
	GeneratePlatformList();

}

void AFallablePlatformController::ResetPlatformList()
{
	UE_LOG(LogTemp, Display, TEXT("Reset PlatformList"));


}

void AFallablePlatformController::GeneratePlatformList()
{
	UE_LOG(LogTemp, Display, TEXT("Generate PlatformList"));


	if (PlatformClass.Get())
	{

		FVector Loc = GetActorLocation();
		FRotator Rotation = FRotator::ZeroRotator;
		AActor* actor = GetWorld()->SpawnActor<AActor>(PlatformClass, Loc, Rotation);

		if (actor)
		{
			PlatformList.Add(actor);
		}
	}

}
