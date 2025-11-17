// Fill out your copyright notice in the Description page of Project Settings.


#include "Coin.h"
#include"PlatfomerPR/PlatfomerPRCharacter.h"
#include<Kismet/GameplayStatics.h>
#include"PlatfomerPR/PlatformerGameMode.h"

void ACoin::Tick(float DeltaTime)
{

	FRotator Rotator = GetActorRotation();
	Rotator.Yaw += RotationSpeedDegree * DeltaTime;;
	SetActorRotation(Rotator);

}

void ACoin::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	APlatfomerPRCharacter* Player = Cast<APlatfomerPRCharacter>(OtherActor);
	if (Player)
	{
		if (CoinSound)
		{


			UGameplayStatics::PlaySoundAtLocation(this, CoinSound, GetActorLocation());
		}

		APlatformerGameMode* gameMode = Cast<APlatformerGameMode>(GetWorld()->GetAuthGameMode());
		if (gameMode)
		{
			gameMode->IncreaseCollectedCoinCount();
		}


		Destroy();
	}

}

void ACoin::OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{




}

