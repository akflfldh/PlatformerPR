// Fill out your copyright notice in the Description page of Project Settings.


#include "StageActor.h"

// Sets default values
AStageActor::AStageActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshCom"));


}

// Called when the game starts or when spawned
void AStageActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AStageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FString AStageActor::GetStageName() const
{
	return StageName;
}