// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelPortal.generated.h"

class UBoxComponent;

UCLASS()
class PLATFOMERPR_API ALevelPortal : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelPortal();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	virtual bool CanEnterNextLevel() const;

	//다음 레벨로 이동
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	FString GetNextLevelStr() const;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:




private:

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* TriggerComponent;


	UPROPERTY(EditanyWhere)
	FString NextLevel;


};
