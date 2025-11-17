// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Energy.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class USoundBase;

UCLASS()
class PLATFOMERPR_API AEnergy : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AEnergy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


protected:
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);




private:


	UPROPERTY(EditAnywhere, Category = "Component")
	UBoxComponent* TriggerComponent;

	UPROPERTY(EditAnywhere, Category = "Component")
	UStaticMeshComponent* StaticMeshComponent;


	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* PickupSound;


};
