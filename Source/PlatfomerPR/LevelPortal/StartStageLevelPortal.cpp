// Fill out your copyright notice in the Description page of Project Settings.


#include "StartStageLevelPortal.h"
#include<Kismet/GameplayStatics.h>
#include "PlatfomerPR/Interface/InteractInterface.h"
#include"PlatfomerPR/GameMode/StartStageGameMode.h"

AStartStageLevelPortal::AStartStageLevelPortal()
{
}

void AStartStageLevelPortal::Interact(APlatfomerPRCharacter* player, EPlayerInputType inputType)
{

	if (inputType == EPlayerInputType::EEnterPortal)
	{
		AStartStageGameMode* GameMode = Cast< AStartStageGameMode>(UGameplayStatics::GetGameMode(this));
		//조건 : 플레이어가 에네지를 모두 모았는가? 
		//GameMode에서 확인

		if (GameMode)
		{
			if (GameMode->GetCurrentEnergy() >= EnergyCondition)
			{
				UGameplayStatics::OpenLevel(this, FName(GetNextLevelStr()));
			}
		}
	}
}


void AStartStageLevelPortal::BeginPlay()
{
	Super::BeginPlay();
}

void AStartStageLevelPortal::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{


	//F키 활성화 




}
