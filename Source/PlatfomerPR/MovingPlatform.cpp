// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void AMovingPlatform::SetMoveState(bool flag)
{
	bMoveState = flag;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartPosition = GetActorLocation();

	TargetPositionWorld = GetRootComponent()->GetComponentTransform().TransformPosition(TargetPosition);


	UpdateDirection();


}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	Move(DeltaTime);

}

void AMovingPlatform::Move(float DeltaTime)
{

	if (bMoveState)
	{
		//TargetPosition까지 이동했다 다시 시작지점으로 이동 반복 


		SetActorLocation(GetActorLocation() + Speed * DeltaTime * DirectionToTargetNormal);


		float toActorDistance = (GetActorLocation() - StartPosition).Length();
		float DirDistance = DirectionToTargetWorld.Length();

		if (toActorDistance > DirDistance)
		{
			//swap 
			Swap(StartPosition, TargetPositionWorld);
			SetActorLocation(StartPosition);


			UpdateDirection();

		}
	}
	else
	{


	}


}

void AMovingPlatform::UpdateDirection()
{
	DirectionToTargetWorld = TargetPositionWorld - StartPosition;
	DirectionToTargetNormal = DirectionToTargetWorld.GetSafeNormal();
}

