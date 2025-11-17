// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StageActor.generated.h"

class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class PLATFOMERPR_API AStageActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AStageActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FString GetStageName() const;

private:

	UPROPERTY(EditAnywhere, Category = "Stage")
	FString StageName;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	TObjectPtr < UStaticMeshComponent> StaticMeshComponent;



};
