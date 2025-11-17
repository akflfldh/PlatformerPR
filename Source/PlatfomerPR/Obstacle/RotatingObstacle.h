// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingObstacle.generated.h"

class UBoxComponent;
class APlatfomerPRCharacter;
UCLASS()
class PLATFOMERPR_API ARotatingObstacle : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARotatingObstacle();


	FVector GetRotationAxis() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Rotate(float DeltaTime);

	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	//범위에서 벗어남
	UFUNCTION()
	void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);





public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;






private:

	UPROPERTY(EditAnywhere)
	FVector RotationAxis = { 0,0,0 };

	UPROPERTY(EditAnywhere)
	UBoxComponent* HitComponent1;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* StaticMeshCom;




};
