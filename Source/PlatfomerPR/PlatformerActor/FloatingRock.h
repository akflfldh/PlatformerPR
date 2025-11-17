// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingRock.generated.h"

class USphereComponent;

UCLASS()
class PLATFOMERPR_API AFloatingRock : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFloatingRock();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;




protected:

	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<UStaticMeshComponent> StaticMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr<USphereComponent> FloatingDownTriggerComponent;


	UFUNCTION()
	void OnBeginOverlapFloatingDown(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnEndOverlapFloatingDown(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;





private:


	UPROPERTY(EditAnywhere, Category = "Reference")
	float FloatingDistance = 10.0f;

	UPROPERTY(EditAnywhere, Category = "Reference")
	float FloatingSpeed = 3.0f;

	FVector StartLocation;

	void Floating(float DeltaTime);

	int FloatingDIr = 1;

	bool bFloatingDown = false;


	UPROPERTY(EditAnywhere, Category = "Reference")
	float FloatingDownSpeed = 3.0f;
};
