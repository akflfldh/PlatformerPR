// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SwingingObstacle.generated.h"

class UBoxComponent;

UCLASS()
class PLATFOMERPR_API ASwingingObstacle : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASwingingObstacle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere)
	UBoxComponent* HitTriggerComponent;

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* HitStaticMeshComponent;


	UPROPERTY(EditAnywhere)
	float MaxSwingAngle = 30.0f;

	//각도
	UPROPERTY(EditAnywhere)
	float SwingSpeed = 50.0f;


	float CurrentSwingAngle = 0.0f;


	int CurrentSwingdDir = 1;



};
