// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPlatform.generated.h"

class UBoxComponent;
class USoundBase;
UCLASS()
class PLATFOMERPR_API ALaunchPlatform : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALaunchPlatform();






protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;




private:


	UPROPERTY(VisibleAnywhere)

	UBoxComponent* TriggerVolume;



	UPROPERTY(EditAnywhere)
	USoundBase* HitSound;


private:

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



	UPROPERTY(EditAnywhere)
	FVector LaunchVelocity;



};
