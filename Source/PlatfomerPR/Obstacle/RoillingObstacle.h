// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RoillingObstacle.generated.h"

class APlatfomerPRCharacter;
class UBoxComponent;

UCLASS()
class PLATFOMERPR_API ARoillingObstacle : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARoillingObstacle();

	void SetTargetLocation(const FVector& targetLocation);
	void SetSpeed(float speed);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshCom;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* ForceCom;


	APlatfomerPRCharacter* PlayerCharacter;

	FVector StartLocation;
	FVector TargetLocation;

	FVector DirWorld;
	FVector DirNormal;


	UPROPERTY(EditAnywhere)
	float Speed = 30.0f;;
};
