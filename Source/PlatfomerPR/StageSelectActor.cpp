// Fill out your copyright notice in the Description page of Project Settings.


#include "StageSelectActor.h"

// Sets default values
AStageSelectActor::AStageSelectActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMeshCom"));

}

// Called when the game starts or when spawned
void AStageSelectActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AStageSelectActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

