// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemActor.h"
#include "Coin.generated.h"

/**
 *
 */
UCLASS()
class PLATFOMERPR_API ACoin : public AItemActor
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

protected:

	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	//범위에서 벗어남
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

private:
	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* CoinSound;


	UPROPERTY(EditAnywhere, Category = "Refernce")
	float RotationSpeedDegree = 30.0f;

};


