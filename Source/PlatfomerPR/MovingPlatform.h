// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class PLATFOMERPR_API AMovingPlatform : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AMovingPlatform();

	void SetMoveState(bool flag);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Move(float DeltaTime);


	FVector StartPosition;


	UPROPERTY(EditAnywhere, Meta = (MakeEditWidget = true))
	FVector TargetPosition;
	FVector TargetPositionWorld;



	FVector DirectionToTargetWorld;
	FVector DirectionToTargetNormal;

	UPROPERTY(EditAnywhere)
	float Speed = 0.0F;


	bool bMoveState = true;

private:


	void UpdateDirection();






};
