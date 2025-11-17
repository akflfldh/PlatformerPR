// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PlatfomerPR/LevelPortal.h"
#include"PlatfomerPR/Interface/InteractInterface.h"
#include "StartStageLevelPortal.generated.h"

/**
 *
 */
UCLASS()
class PLATFOMERPR_API AStartStageLevelPortal : public ALevelPortal, public IInteractInterface
{
	GENERATED_BODY()


public:
	AStartStageLevelPortal();


	void Interact(APlatfomerPRCharacter* player, EPlayerInputType inputType) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//다음 레벨로 이동
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

private:


	UPROPERTY(EditAnywhere)
	int EnergyCondition = 1;

};
